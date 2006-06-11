// vim:tabstop=4:shiftwidth=4:noexpandtab:textwidth=80
/*
 * =====================================================================================
 *        Filename:  pdfopertorsiter.cc
 *         Created:  06/11/2006 01:33:34 PM CET
 *          Author:  jmisutka (), 
 * =====================================================================================
 */

// static
#include "static.h"
//
#include "pdfoperatorsiter.h"

//==========================================================
namespace pdfobjects {
//==========================================================

//==========================================================
// Iterators
//==========================================================

/** Text iterator accepted operators. */
template<>
const std::string TextOperatorIterator::accepted_opers[TextOperatorIterator::namecount] = {"Tj", "TJ", "'", "\""};
/** Inline image iterators. */
template<>
const std::string InlineImageOperatorIterator::accepted_opers[InlineImageOperatorIterator::namecount] = {"BI"};
/** Changeable operator are all operators except these. */
template<>
const std::string ChangeableOperatorIterator::rejected_opers[ChangeableOperatorIterator::namecount] = 
{
	"q", "Q", "cm", "w", "J", "j", "M", "d", "ri", "i", "gs", "s", "S", "f", "F", "f*", "B", "B*", "b", "b*"
	"n", "W", "W*", "BX", "EX", "rg", "CS", "cs", "SC", "SCN", "sc", "scn", "G", "g", "RG", "rg", "K", "k"
};
/** Non stroking iterator accepted operators. */
template<>
const std::string NonStrokingOperatorIterator::accepted_opers[NonStrokingOperatorIterator::namecount] = 
{
	"Tj", "TJ", "'", "\""
};
/** Stroking iterator accepted operators. */
template<>
const std::string StrokingOperatorIterator::accepted_opers[StrokingOperatorIterator::namecount] = 
{
	"", "", "", ""
};

/** Operators accepted by font iterator. */
template<>
const std::string FontOperatorIterator::accepted_opers[FontOperatorIterator::namecount] = 
{
	"Tf", "", "", ""
};

/** Operators accepted by font iterator. */
template<>
const std::string GraphicalOperatorIterator::accepted_opers[GraphicalOperatorIterator::namecount] = 
{
	"f", "F", "f*", "B", "S", "s", "b", "B", "B*", "n", "m", "l", "c", "v", "y", "h", "re", "w", "J", "j",
	"M", "d", "ri", "gs"
};


//==========================================================
} // namespace pdfobjects
//==========================================================