#ifndef __VISUALISATION_VTK_HPP_INCLUDED__
#define __VISUALISATION_VTK_HPP_INCLUDED__

#include "visualization.hpp"

namespace wif_viz
{


class visualization_vtk_c : public visualization_c
{
public:
	visualization_vtk_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range);

	virtual ~visualization_vtk_c();

	//

	virtual void draw(const std::string & filename = "");

private:
	//
};


} // namespace wif_viz

#endif // __VISUALISATION_VTK_HPP_INCLUDED__

