#ifndef __VISUALISATION_ROOT_HPP_INCLUDED__
#define __VISUALISATION_ROOT_HPP_INCLUDED__

#include "visualization.hpp"
#include <TROOT.h>
#include <THistPainter.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMarker.h>
#include <TArrow.h>
namespace wif_viz
{


class visualization_root_c : public visualization_c
{
public:
	visualization_root_c(std::shared_ptr<flow_c> flow, const vector_2d_c & min_range, const vector_2d_c & max_range);

	virtual ~visualization_root_c();

	virtual void draw(const std::string & filename = "");

protected:

	//
};


} // namespace wif_viz

#endif // __VISUALISATION_ROOT_HPP_INCLUDED__

