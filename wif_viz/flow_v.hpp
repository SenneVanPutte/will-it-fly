#ifndef __WIF_VIZ_HPP_INCLUDED__
#define __WIF_VIZ_HPP_INCLUDED__

#include <cstdint>
#include "flow_c.hpp"

namespace wif_viz
{

class flow_v
{
public:
	flow_v();
	
	~flow_v();
	
	void fill_arrows(&vtkRenderWindow);
	
	void fill_contours(&vtkRenderWindow);
	
	void draw_line();
	
	void draw_point();
	
	void print();
	
protected:
	flow_c stream;
	
private:	
	
}


} // namespace wif_viz

#endif // __WIF_VIZ_HPP_INCLUDED__
