#ifndef __SOURCE_SHEET_C_HPP_INCLUDED__
#define __SOURCE_SHEET_C_HPP_INCLUDED__

#include "flow_sheet_c.hpp"

namespace wif_core
{

class source_sheet_c : public flow_sheet_c
{
	public:
		source_sheet_c(const line_2d_c &,double);

		virtual ~source_sheet_c();

		double psi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;

		double phi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;

		vector_2d_c v_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const;

		double sigma;

	protected:
	private:
};

}

#endif // __SOURCE_SHEET_HPP_INCLUDED__
