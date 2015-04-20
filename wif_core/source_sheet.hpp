#ifndef SOURCE_SHEET_HPP_INCLUDED
#define SOURCE_SHEET_HPP_INCLUDED

#include "flow_sheet.hpp"

namespace wif_core
{

class source_sheet : public flow_sheet
{
	public:
		source_sheet(const line_2d_c &,double);
		virtual ~source_sheet();

		double psi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;
		double phi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;
		vector_2d_c v_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;

		double sigma;

	protected:
	private:
};

}

#endif // SOURCE_SHEET_HPP_INCLUDED
