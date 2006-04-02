/*
 * =====================================================================================
 *        Filename:  testcobject.cc
 *         Created:  04/01/2006 12:27:27 AM CEST
 *          Author:  jmisutka (), 
 * =====================================================================================
 */

#include "testmain.h"
#include "testcobject.h"

#include <PDFDoc.h>
#include "../ccontentstream.h"


//
// examples
//
typedef struct
{
	string value;
	string expected;
	union {	
		GBool xb;		//   boolean
		int xi;			//   integer
		double xr;		//   real
		GString *xs;	//   string
		char* xn;		//   name
		Ref xref;		//   indirect reference
	};
	union {	
		bool b;			//   boolean
		int i;			//   integer
		double r;		//   real
		string* s;		//   string
		string* n;		//   name
		IndiRef* ref;	//   indirect reference
	};
	
} example_item;

typedef struct
{
	// simple
	example_item	b;
	example_item	i;
	example_item	r;
	example_item	s;
	example_item	n;
	example_item	ref;

	// complex
	string			arTest1;
	string			arTest2;
	string			dcTest1;
	string			dcTest2;

} example;



//=====================================================================================
// CObjectSimple
//



//====================================================

//
//
//
void 
s_clone ()
{
	CNull null;
	boost::shared_ptr<IProperty> ptr = null.clone ();

	if (ptr)
		OUTPUT << "null.getType(): " << null.getType () << endl;
	else 
		throw;
}

//====================================================

//
//
//
void 
s_ctors (const example& e)
{
	Object obj;
	CPdf pdf;
	IndiRef ref;
	
	// bool
	obj.initBool (e.b.xb);
	CBool bl (pdf, obj, ref);
	ip_validate (bl,e.b.expected);

	// int
	obj.initInt (e.i.xi);
	CInt i (pdf,obj,ref);
	ip_validate (i,e.i.expected);
	
	// Real
	obj.initReal (e.r.xr);
	CReal r (pdf,obj,ref);
	ip_validate (r,e.r.expected);
	
	// String
	obj.initString (e.s.xs);
	CString s (pdf,obj,ref);
	ip_validate (s,e.s.expected);

	
	// Name
	obj.initName (e.n.xn);
	CName n (pdf,obj,ref);
	ip_validate (n,e.n.expected);
	//
	// NAME IS COPIED !!!! fuck xpdf
	//		
	obj.free ();
	
	// Ref
	obj.initRef (e.ref.xref.num,e.ref.xref.gen);
	CRef f (pdf,obj,ref);
	ip_validate (f,e.ref.expected);
}

//====================================================

namespace
{
	template<typename T,typename U>
	void _s_ctors2 (const U var, const string& expected)
	{
			T cl (var);
			ip_validate (cl,expected);
	}

}

//
//
//
void 
s_ctors2 (const example& e)
{
	// bool
	_s_ctors2<CBool> (e.b.b,e.b.expected);
	// int
	_s_ctors2<CInt> (e.i.i,e.i.expected);
	// Real
	_s_ctors2<CReal> (e.r.r,e.r.expected);
	// String
	_s_ctors2<CString> (*(e.s.s),e.s.expected);
	// Name
	_s_ctors2<CName> (*(e.n.n),e.n.expected);
	// Ref
	_s_ctors2<CRef> (*(e.ref.ref),e.ref.expected);

	// Null
	CNull null;
	ip_validate (null, "null");
}

//====================================================

namespace
{
	template<typename T,typename U>
	void _s_setString (const U var, const string& expected)
	{
			T cl;
			cl.setStringRepresentation (var);
			ip_validate (cl,expected);
	}

}

//
//
//
void 
s_setString (const example& e)
{
	// bool
	_s_setString<CBool> (e.b.value,e.b.expected);
	// int
	_s_setString<CInt> (e.i.value,e.i.expected);
	// Real
	_s_setString<CReal> (e.r.value,e.r.expected);
	// String
	_s_setString<CString> (e.s.value,e.s.expected);
	// Name
	_s_setString<CName> (e.n.value,e.n.expected);
	// Ref
	_s_setString<CRef> (e.ref.value,e.ref.expected);

	// should get compile error
	// CNull null;
	// null.setStringRepresentation ("");
}

//====================================================

namespace
{
	template<typename T,PropertyType Tp>
	void _s_getTp ()
	{
			T cl;
			ip_validate (Tp,cl.getType ());
	}

}

//
//
//
void 
s_getTp ()
{
	// bool
	_s_getTp<CBool,pBool> ();
	// int
	_s_getTp<CInt,pInt> ();
	// Real
	_s_getTp<CReal,pReal> ();
	// String
	_s_getTp<CString,pString> ();
	// Name
	_s_getTp<CName,pName> ();
	// Ref
	_s_getTp<CRef,pRef> ();
	// Null
	_s_getTp<CNull,pNull> ();
}


//====================================================

namespace
{
	template<typename T,typename U>
	void _s_writeVal (const U var, const string& expected)
	{
			T cl;
			cl.writeValue (var);
			ip_validate (cl,expected);
	}

}

//
//
//
void 
s_writeVal (const example& e)
{
	// bool
	_s_writeVal<CBool> (e.b.b,e.b.expected);
	// int
	_s_writeVal<CInt> (e.i.i,e.i.expected);
	// Real
	_s_writeVal<CReal> (e.r.r,e.r.expected);
	// String
	_s_writeVal<CString> (*(e.s.s),e.s.expected);
	// Name
	_s_writeVal<CName> (*(e.n.n),e.n.expected);
	// Ref
	_s_writeVal<CRef> (*(e.ref.ref),e.ref.expected);

	// should get compile error
	// CNull null;
	// null.writeValue ("");

}

//====================================================

namespace
{
	template<typename T,typename U>
	void _s_getVal (const U expected)
	{
			T cl;
			cl.writeValue (expected);
			U val;
			cl.getPropertyValue (val);
			ip_validate (val,expected);
	}
}

void 
s_getVal (const example& e)
{
	// bool
	_s_getVal<CBool> (e.b.b);
	// int
	_s_getVal<CInt> (e.i.i);
	// Real
	_s_getVal<CReal> (e.r.r);
	// String
	_s_getVal<CString> (*(e.s.s));
	// Name
	_s_getVal<CName> (*(e.n.n));
	// Ref
	_s_getVal<CRef> (*(e.ref.ref));

	// should get compile error
	// CNull null;
	// null.getPropertyValue ();

}

//====================================================

namespace
{
	template<typename T,typename U>
	void _s_makeXpdf (const U var, const string& expected)
	{
			Object* obj;
			T cl;
			cl.writeValue (var);
			obj = cl._makeXpdfObject ();
			ip_validate (obj,expected);
			utils::freeXpdfObject (obj);
	}

}

//
//
//
void 
s_makeXpdf (const example& e)
{
	// bool
	_s_makeXpdf<CBool> (e.b.b,e.b.expected);
	// int
	_s_makeXpdf<CInt> (e.i.i,e.i.expected);
	// Real
	_s_makeXpdf<CReal> (e.r.r,e.r.expected);
	// String
	_s_makeXpdf<CString> (*(e.s.s),e.s.expected);
	// Name
	_s_makeXpdf<CName> (*(e.n.n),e.n.expected);
	// Ref
	_s_makeXpdf<CRef> (*(e.ref.ref),e.ref.expected);

	// should get compile error
	// CNull null;
	// null.getPropertyValue ();

}


//====================================================

void
s_rel ()
{
	CString cstr ("raz dva tri");
	boost::shared_ptr<IProperty> ip = cstr.clone (); // object UNALLOCATED

}


//=====================================================================================
// CObjectComplex
//=====================================================================================



void
c_clone ()
{
	CDict dict;

	CString item1 ("fero");
	dict.addProperty ("jano", item1);
	
	boost::shared_ptr<IProperty> clone_ = dict.clone (); // 2x objects allocated
	ip_validate (dict, *clone_);
}


//=====================================================================================

void
c_smrt ()
{
	CDict dict; 
	CString val1 ("val1");
	CString val2 ("val2");
	dict.addProperty ("item1", val1);
	dict.addProperty ("item2", val2);

// BAD HABBIT
	CString* ptrStr1 = new CString ("val3");	// UNALLOCATED if not freed manually
	dict.addProperty ("item3", *ptrStr1);
	delete ptrStr1;
// GOOD HABBIT
	boost::shared_ptr<IProperty> ptrStr2 (new CString ("val4"));
	dict.addProperty ("item4", *ptrStr2);
// EVEN BETTER HABBIT
	CString str3 ("val5");
	dict.addProperty ("item5", str3);
// BEST HABBIT -- not functional (yet)
	//dict.addProperty ("item5", CString ("val6"));

	//OUTPUT << dict;
	
	boost::shared_ptr<IProperty> ipp1 = dict.getProperty ("item3");
	boost::shared_ptr<IProperty> ipp2 = dict.getProperty ("item4");
	boost::shared_ptr<IProperty> ipp3 = dict.getProperty ("item5");

	ip_validate (*ipp1, "(val3)");
	ip_validate (*ipp2, "(val4)");
	ip_validate (*ipp3, "(val5)");
}

//=====================================================================================

namespace
{
	template<typename U, PropertyType Tp>
	void
	_c_getTp ()
	{
		U obj;
		ip_validate (Tp, obj.getType ());
	}
}

void
c_getTp ()
{
	// Array
	_c_getTp<CArray,pArray> ();
	// Dict
	_c_getTp<CDict,pDict> ();
	// Stream
	//_c_getTp<CStream,pStream> ();


}

//=====================================================================================

void
mdctrl ()
{
	CPdf pdf;
	pdf.getModeController ();
}


//=====================================================================================



namespace
{
	void
	makeArTest1 (CArray& arTest1)
	{
		//
		// Make an array, simple values
		//
		CString it1 ("item1");
		CString it2 ("item2");
		CString it3 ("item3");
		arTest1.addProperty (it1);
		arTest1.addProperty (it2);
		arTest1.addProperty (it3);
		CInt i1 (1);
		CInt i2 (2);
		CInt i3 (3);
		CInt i4 (4);
		arTest1.addProperty (i1);
		arTest1.addProperty (i2);
		arTest1.addProperty (i3);
		arTest1.addProperty (i4);
		IndiRef ref = {3,4};
		CRef rf (ref);
		arTest1.addProperty (rf);
		CBool bl (false);
		arTest1.addProperty (bl);

	}

	void
	makeDcTest1 (CDict& dcTest1)
	{
		//
		// Make a dictionary, simple values
		//
		CString it1 ("item1");
		CString it2 ("item2");
		CString it3 ("item3");
		dcTest1.addProperty ("item1", it1);
		dcTest1.addProperty ("item2", it2);
		dcTest1.addProperty ("item3", it3);
		CInt i1 (1);
		CInt i2 (2);
		CInt i3 (3);
		CInt i4 (4);
		dcTest1.addProperty ("item4", i1);
		dcTest1.addProperty ("item5", i2);
		dcTest1.addProperty ("item6", i3);
		dcTest1.addProperty ("item7", i4);
		IndiRef ref = {3,4};
		CRef rf (ref);
		dcTest1.addProperty ("item8", rf);
		CBool bl (false);
		dcTest1.addProperty ("item9", bl);

	}

	void
	makeArTest2 (CArray& arTest2, CArray& arTest1, CDict& dcTest1)
	{
		arTest2.addProperty (arTest1);
		arTest2.addProperty (arTest1);
		arTest2.addProperty (arTest1);
		arTest2.addProperty (dcTest1);
		arTest2.addProperty (dcTest1);
		arTest2.addProperty (dcTest1);
	}

	void
	makeDcTest2 (CDict& dcTest2, CArray& arTest1, CDict& dcTest1)
	{
		dcTest2.addProperty ("1", arTest1);
		dcTest2.addProperty ("2", arTest1);
		dcTest2.addProperty ("3", arTest1);
		dcTest2.addProperty ("4", dcTest1);
		dcTest2.addProperty ("5", dcTest1);
		dcTest2.addProperty ("6", dcTest1);
	}
		
}

void
c_getString (const example& e)
{
		
	CArray arTest1;
	CArray arTest2;
	CDict dcTest1;
	CDict dcTest2;

	makeArTest1 (arTest1);
	ip_validate (arTest1, e.arTest1);

	makeDcTest1 (dcTest1);
	ip_validate (dcTest1, e.dcTest1, false);

	makeArTest2 (arTest2, arTest1, dcTest1);
	ip_validate (arTest2, e.arTest2, false); 

	makeDcTest2 (dcTest2, arTest1, dcTest1);
	ip_validate (dcTest2, e.dcTest2, false); 
}


//=====================================================================================

void
c_getCnt ()
{
		
	CArray arTest1;
	CArray arTest2;
	CDict dcTest1;
	CDict dcTest2;

	makeArTest1 (arTest1);
	ip_validate (arTest1.getPropertyCount (), 9);

	makeDcTest1 (dcTest1);
	ip_validate (dcTest1.getPropertyCount (), 9);

	
	makeArTest2 (arTest2, arTest1, dcTest1);
	ip_validate (arTest2.getPropertyCount (), 6); 

	makeDcTest2 (dcTest2, arTest1, dcTest1);
	ip_validate (dcTest2.getPropertyCount (), 6); 
}

//=====================================================================================

void
c_getNames ()
{
		
	CArray arTest1;
	CDict dcTest1;
	CDict dcTest2;

	// create Array 1
	makeArTest1 (arTest1);

	//
	// expected item1, ... ,item9
	//
	vector<string> expected;
	for (int i = 1; i <= 9; ++i)
	{
		ostringstream oss;
		oss << i;
		expected.push_back (string ("item" + oss.str()));
	}
	
	// create dictionary 1
	makeDcTest1 (dcTest1);
	vector<string> names;
	dcTest1.getAllPropertyNames (names);
	ip_validate (names, expected);

	//
	// reset string
	//
	expected.clear ();
	names.clear ();
	
	//
	// other 1, ... ,9
	//
	for (int i = 1; i <= 9; ++i)
	{
		ostringstream oss;
		oss << i;
		expected.push_back (string (oss.str()));
	}

	makeDcTest2 (dcTest2, arTest1, dcTest1);
	dcTest2.getAllPropertyNames (names);
	ip_validate (names, expected); 
}

		
//=====================================================================================
		
void
c_getType ()
{
		
	CArray arTest1;
	CDict dcTest1;

	// create Array 1
	makeArTest1 (arTest1);
	for (size_t i = 0; i < arTest1.getPropertyCount (); ++i)
	{
		boost::shared_ptr<IProperty> ip = arTest1.getProperty (i);
		ip_validate (arTest1.getPropertyType (i), ip->getType ());
	}
	
	
	// create dictionary 1
	makeDcTest1 (dcTest1);
	vector<string> names;
	dcTest1.getAllPropertyNames (names);
	
	for (vector<string>::iterator it = names.begin(); it != names.end(); ++it)
	{
		boost::shared_ptr<IProperty> ip = dcTest1.getProperty (*it);
		ip_validate (dcTest1.getPropertyType (*it), ip->getType ());
	}

}

//=====================================================================================

void
c_xpdf (const example& e)
{

	CArray arTest1;
	CArray arTest2;
	CDict dcTest1;
	CDict dcTest2;
	string tmp;

	makeArTest1 (arTest1);
	Object* obj = arTest1._makeXpdfObject ();
	arTest1.getStringRepresentation (tmp);
	ip_validate (obj, e.arTest1);
	ip_validate (obj, tmp);
	utils::freeXpdfObject (obj);

	makeDcTest1 (dcTest1);
	obj = dcTest1._makeXpdfObject ();
	dcTest1.getStringRepresentation (tmp);
	ip_validate (obj, e.dcTest1, false);
	ip_validate (obj, tmp);
	utils::freeXpdfObject (obj);

	makeArTest2 (arTest2, arTest1, dcTest1);
	obj = arTest2._makeXpdfObject ();
	arTest2.getStringRepresentation (tmp);
	ip_validate (obj, e.arTest2, false);
	ip_validate (obj, tmp);
	utils::freeXpdfObject (obj);


	makeDcTest2 (dcTest2, arTest1, dcTest1);
	obj = dcTest2._makeXpdfObject ();
	dcTest2.getStringRepresentation (tmp);
	ip_validate (obj, e.dcTest2, false);
	ip_validate (obj, tmp);
	utils::freeXpdfObject (obj);
}

//=====================================================================================

void
c_del ()
{

	CArray arTest1;
	CArray arTest2;
	CDict dcTest1;
	CDict dcTest2;

	//
	//
	//
	makeArTest1 (arTest1);
	while (0 != arTest1.getPropertyCount())
		arTest1.delProperty (0);
	ip_validate (arTest1,"[ ]");

	//
	//
	//
	makeDcTest1 (dcTest1);
	list<string> names;
	dcTest1.getAllPropertyNames (names);
	for (list<string>::iterator it = names.begin (); it != names.end (); ++it)
		dcTest1.delProperty (*it);
	ip_validate (dcTest1,"<<\n>>");

	//
	//
	//
	makeArTest2 (arTest2, arTest1, dcTest1);
	while (0 != arTest2.getPropertyCount())
		arTest2.delProperty (0);
	ip_validate (arTest2,"[ ]");

	//
	//
	//
	makeDcTest2 (dcTest2, arTest1, dcTest1);
	names.clear ();
	dcTest2.getAllPropertyNames (names);
	for (list<string>::iterator it = names.begin (); it != names.end (); ++it)
		dcTest2.delProperty (*it);
	ip_validate (dcTest2,"<<\n>>");
}


//=====================================================================================

void
c_set ()
{

	CArray a;
	CDict d;

	CInt i1 (1);	CInt i2 (2);	CInt i3 (3);
	CString s1 ("s1");	CString s2 ("s2");	CString s3 ("s3");

	a.addProperty (i1);			a.addProperty (i2);			a.addProperty (i3);
	ip_validate (a,"[ 1 2 3 ]");
	
	a.setProperty (0,s1);	a.setProperty (1,s2);	a.setProperty (2,s3);
	ip_validate (a,"[ (s1) (s2) (s3) ]");

	d.addProperty ("1", i1);		d.addProperty ("2", i2);		d.addProperty ("3", i3);
	ip_validate (d,"<<\n/1 1\n/2 2\n/3 3\n>>", false);
	
	d.setProperty ("1",s1);	d.setProperty ("2",s2);	d.setProperty ("3",s3);
	ip_validate (d,"<<\n/1 (s1)\n/2 (s2)\n/3 (s3)\n>>", false);
}

//=====================================================================================

void
c_xpdfctor ()
{
	{
		//
		// Array
		//
		Object obj;
		obj.initArray (NULL);

		Object item1; item1.initBool	(gFalse);
		Object item2; item2.initBool	(gTrue);
		Object item3; item3.initInt	(-43);
		Object item4; item4.initString	(new GString ("item4"));

		obj.arrayAdd (&item1);
		obj.arrayAdd (&item2);
		obj.arrayAdd (&item3);
		obj.arrayAdd (&item4);
		
		CPdf pdf;
		IndiRef ref = {12,11};
		CArray ar (pdf,obj,ref);

		ip_validate (obj,ar);
		
		obj.free ();
	}
	{
		//
		// Dict
		//
		Object obj;
		obj.initDict ((XRef*)NULL);

		Object item1; item1.initBool	(gFalse);
		Object item2; item2.initBool	(gTrue);
		Object item3; item3.initInt	(-43);
		Object item4; item4.initString	(new GString ("item4"));

		char* it1 = strdup ("lajno1");
		char* it2 = strdup ("lajno2");
		char* it3 = strdup ("lajno3");
		char* it4 = strdup ("lajno4");
		obj.dictAdd (it1, &item1);
		obj.dictAdd (it2, &item2);
		obj.dictAdd (it3, &item3);
		obj.dictAdd (it4, &item4);

		CPdf pdf;
		IndiRef ref = {12,11};
		// CArray ar (pdf,obj,ref); // GOOOOOD -- assertation failed
		CDict dc (pdf,obj,ref); 
		
		ip_validate (obj,dc);
		ip_validate (dc, "<<\n/lajno1 false\n/lajno2 true\n/lajno3 -43\n/lajno4 (item4)\n>>");
		
		obj.free ();
	}
	
}

//=====================================================================================
// CContentStream
//=====================================================================================

void
getContentStream (ostream& oss, const char* fileName, bool allPages)
{
	boost::scoped_ptr<PDFDoc> doc (new PDFDoc (new GString(fileName), NULL, NULL));
	int pagesNum = (allPages) ? doc->getNumPages() : 1;
	
	oss << "Filename: " << fileName << endl;
	oss << "Number of pages: " << pagesNum << endl;

	//
	// Our stuff here
	//
	Object obj;
	XRef* xref = doc->getXRef();
	Catalog cat (xref);

	oss << "Trailer:" << xref->getTrailerDict () << endl;
	oss << "Catalog:" << xref->getCatalog (&obj) << endl;
	
	for (int i = 1; i <= pagesNum; ++i)
	{
		oss << "Page:"			<< xref->fetch (cat.getPageRef(i)->num, cat.getPageRef(i)->gen, &obj) << endl;
		oss << "Contents:"		<< cat.getPage(i)->getContents(&obj) << endl;
//		oss << "StreamDict:\n"	<< cat.getPage(i)->getContents(&obj)->getStream()->getDict() << endl;
//		oss << "Stream:\n";		print (oss, cat.getPage(i)->getContents(&obj), xref);
	}
	
	assert (xref->getDocInfo (&obj));
	oss << "Doc info:" << &obj << endl;

}

extern const char OPER_STR1[] = "Td";

void
test_ccontentstream ()
{
	boost::shared_ptr<CInt> i (new CInt(3));
	boost::shared_ptr<CString> s (new CString ("123"));
	
	PdfOperator::Operands p;
	p.push_back (i);
	p.push_back (s);
	p.push_back (i);
	p.push_back (i);
	p.push_back (i);

	///////// -- construct
	SimpleGenericOperator example ("ADS", 5, p);
	
	///////// -- bad function usage
	bool exc = false;
	try {
			
		example.push_back (boost::shared_ptr<PdfOperator> ());
		
	}catch (...)
	{
		exc = true;
	}
	if (!exc)
		throw;

	///////// -- getStringRepresentation
	std::string str;
	example.getStringRepresentation (str);
	//OUTPUT << "String repre: " << str;
	if ("3 (123) 3 3 3 ADS" != str)
		throw;

	///////// -- getString
	if (5 != example.getParametersCount ())
		throw;
}

void
parseContentStream (ostream& oss, const char* fileName)
{
	CPdf pdf;
	
	boost::scoped_ptr<PDFDoc> doc (new PDFDoc (new GString(fileName), NULL, NULL));
	int pagesNum = 1;
	
	//
	// Our stuff here
	//
	Object obj;
	XRef* xref = doc->getXRef();
	assert (xref);
	Catalog cat (xref);

	cat.getPage(pagesNum)->getContents(&obj);
	
	if (!obj.isStream())
		throw;
	
	Object o;
	PdfOperator::Operands oper;

	vector<boost::shared_ptr<PdfOperator> > pdfopers;
	
	boost::scoped_ptr<Parser> parser (new Parser(xref, new Lexer(xref, &obj)));
	parser->getObj(&o);
	while (!o.isEOF()) 
	{
		if (o.isCmd ())
		{
			pdfopers.push_back (boost::shared_ptr<UnknownPdfOperator> (new UnknownPdfOperator (oper, o.getCmd ())));
			if (!oper.empty ())
			{
				oss << "Not empty after unknown.";
				throw;
			}
				
		}else
		{
			boost::shared_ptr<IProperty> pIp (utils::createObjFromXpdfObj (pdf, o, IndiRef()));
			oper.push_back (pIp);
		}

		o.free ();
		// grab the next object
		parser->getObj(&o);
	}
	obj.free ();

	for (vector<boost::shared_ptr<PdfOperator> >::iterator it = pdfopers.begin ();
					it != pdfopers.end (); ++it)
	{
		static int i = 0;
		string str;
		(*it)->getStringRepresentation (str);

		//oss << str << "\t\t";
		// if (0 == (++i % 3))
			//oss << endl;
	}

}

void
contentStream (ostream& , const char* fileName)
{
	CPdf pdf;
	
	boost::scoped_ptr<PDFDoc> doc (new PDFDoc (new GString(fileName), NULL, NULL));
	int pagesNum = 1;
	
	//
	// Our stuff here
	//
	Object obj;
	XRef* xref = doc->getXRef();
	assert (xref);
	Catalog cat (xref);

	cat.getPage(pagesNum)->getContents(&obj);
	
	if (!obj.isStream())
		throw;
	
	//
	// Parse the file
	//
	boost::shared_ptr<CStream> stream (new CStream(pdf,obj,IndiRef()) );
	CContentStream cc (stream, &obj);

	string tmp;
	cc.getStringRepresentation (tmp);
	//oss << "String representation: " << tmp;

	obj.free ();

}

//=====================================================================================

void
c_addprop2 ()
{
	CDict dict;
	CInt i (1);
	CInt ii (11);

	dict.addProperty ("1", i);
	boost::shared_ptr<IProperty> b = dict.addProperty ("2", ii);
	dict.addProperty ("3", i);
	dict.addProperty ("4", ii);

	if ("2" != dict.getPropertyId (b))
		throw;

	
	CArray a;

	a.addProperty (i);
	boost::shared_ptr<IProperty> bb = a.addProperty (ii);
	a.addProperty (i);
	a.addProperty (ii);
	ip_validate (a,"[ 1 11 1 11 ]");

	if (1 != a.getPropertyId (bb))
		throw;

	CString s ("new");
	a.addProperty (3,s);
	a.addProperty (0,s);
	a.addProperty (6,s);
	ip_validate (a,"[ (new) 1 11 1 (new) 11 (new) ]");
	
	bool exc = false;
	try
	{
		a.addProperty (16,s);
	}catch(...)
	{
		exc = true;
	}
	if (!exc)
		throw;
}


//=====================================================================================
void cobject_tests(int , char **)
{
	
	static example e;

	//
	// TEST EXAMPLE
	//
	// Simple
	//
	e.b.xb			= gFalse;
	e.b.b			= false;
	e.b.value		= "false";
	e.b.expected	= "false";
	
	e.i.xi = e.i.i	= 321;							
	e.i.value		= "321";
	e.i.expected	= "321";
	
	e.r.xr = e.r.r	= -3.2313;						
	e.r.value		= "-3.2313";
	e.r.expected	= "-3.2313";
	
	e.n.xn = new char [100]; strncpy (e.n.xn, "name",10);
	e.n.n = new string ("name");
	e.n.value		= "name";
	e.n.expected	= "/name";
	
	e.s.xs = new GString("string");			
	e.s.s = new string ("string");
	e.s.value		= "string";
	e.s.expected	= "(string)";
	
	e.ref.ref = new IndiRef;
	e.ref.xref.num = e.ref.ref->num = 32;
	e.ref.xref.gen = e.ref.ref->gen = 10;
	e.ref.value	= "32 10";
	e.ref.expected	= "32 10 R";
	//
	// Complex
	//
	e.arTest1 = "[ (item1) (item2) (item3) 1 2 3 4 3 4 R false ]";
	e.dcTest1 = "<<\n/item1 (item1)\n/item2 (item2)\n/item3 (item3)\n/item4 1\n/item5 2\n/item6 "
			    "3\n/item7 4\n/item8 3 4 R\n/item9 false\n>>";
	const string ar2 ("[ "	+ e.arTest1 + " " + e.arTest1 + " " 
							+ e.arTest1 + " " + e.dcTest1 + " " + e.dcTest1 + " " + e.dcTest1 + " ]");
	const string dc2 ("<<\n/1 "	+ e.arTest1 + "\n/2 " + e.arTest1 + "\n/3 " + e.arTest1 + "\n/4 " 
								+ e.dcTest1 + "\n/5 " + e.dcTest1 + "\n/6 " + e.dcTest1 + "\n>>");
	e.arTest2 = ar2;
	e.dcTest2 = dc2;

	//==================== Tests

	TEST(" test 1.0 -- getType_");
	s_getTp ();
	OK_TEST;

	TEST(" test 1.1 -- clone");
	s_clone ();
	OK_TEST;
	
	TEST(" test 1.2 -- getString + constructors");
	s_ctors (e);
	OK_TEST;

	TEST(" test 1.3 -- getString + constructors 2");
	s_ctors2 (e);
	OK_TEST;
	
	TEST(" test 1.4 -- setString");
	s_setString (e);
	OK_TEST;

	TEST(" test 1.5 -- writeValue");
	s_writeVal (e);
	OK_TEST;

	TEST(" test 1.6 -- getPropertyValue");
	s_getVal (e);
	OK_TEST;

	TEST(" test 1.7 -- _makeXpdfObject");
	s_makeXpdf (e);
	OK_TEST;

	TEST(" test 1.8 -- _");
	s_rel ();
	OK_TEST;

	//======================= CObjectComplex
	
	TEST(" test 2.1.0 - getType")
	c_getTp ();
	OK_TEST;

	TEST(" test 2.1 - clone")
	c_clone ();
	OK_TEST;

	TEST(" test 2.2 - smart ptrs")
	c_smrt ();
	OK_TEST;

	TEST(" test 2.3 - mode controller")
	mdctrl ();
	OK_TEST;

	TEST(" test 2.4 - getStringRepre")
	c_getString (e);
	OK_TEST;

	TEST(" test 2.5 - getPropCount")
	c_getCnt ();
	OK_TEST;

	TEST(" test 2.6 - getAllPropNames")
	c_getNames ();
	OK_TEST;

	TEST(" test 2.7 - getType")
	c_getType ();
	OK_TEST;

	TEST(" test 2.8 - makeXpdf")
	c_xpdf (e);
	OK_TEST;

	TEST(" test 2.9 - delProp")
	c_del ();
	OK_TEST;

	TEST(" test 2.9 - setProp")
	c_set ();
	OK_TEST;

	TEST(" test 2.10 - xpdf ctors")
	c_xpdfctor ();
	OK_TEST;

	TEST(" test 2.11 - xpdf addProperty + getPosition")
	c_addprop2 ();
	OK_TEST;

	//======================= CContentStream
	
	TEST(" test 3.1 -- ccontentstream - getContentstream")
	getContentStream (cout, TESTPDFFILE, false);
	OK_TEST;
	
	TEST(" test 3.2 -- ccontentstream - operators")
	test_ccontentstream ();
	OK_TEST;

	TEST(" test 3.3 -- ccontentstream - parse to our operators")
	parseContentStream (cout, TESTPDFFILE);
	OK_TEST;
	
	TEST(" test 3.4 -- ccontentstream - try ccontentstream class to parse a contentstream")
	contentStream (cout, TESTPDFFILE);
	OK_TEST;

}
