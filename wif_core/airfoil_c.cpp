#include "airfoil_c.hpp"

namespace wif_core
{


airfoil_c::airfoil_c(const std::string filename)
{
	//selig format
	std::ifstream data(filename);
	std::string name;
	data >> name;

	while(!data.eof())
	{
		double x;
		double y;
		data >> x >> y;
		points.push_back(vector_2d_c(x, y));
	}
}


airfoil_c::airfoil_c(const std::vector<vector_2d_c> iter)
{
	copy(iter.begin(), iter.end(), this->points.begin());
}


unsigned int airfoil_c::size() const
{
	return(points.size());
}


vector_2d_c & airfoil_c::point(unsigned int index)
{
	return(points[index]);
}


vector_2d_c airfoil_c::get_point(unsigned int index) const
{
	return(points[index]);
}


line_2d_c airfoil_c::get_line(unsigned int index) const
{
	if(index == this->size() - 1)
	{
		line_2d_c r(this->get_point(this->size() - 1), this->get_point(0));
		return(r);
	}
	else
	{
		line_2d_c r(this->get_point(index), this->get_point(index + 1));
		return(r);
	}

}


vector_2d_c airfoil_c::get_intersection_first(const line_2d_c line) const
{
	for(unsigned int i = 0; i < this->size(); i++)
	{
		vector_2d_c intersect(0, 0);
		E_INTERSECTION intersect_type = line.get_intersection(this->get_line(i), intersect);

		if(intersect_type == EI_SEGMENT)
		{
			return(intersect);
		}
	}

	return(vector_2d_c(0, 0));
}

vector_2d_c airfoil_c::get_intersection_last(const line_2d_c line) const
{
	for(unsigned int i = this->size() - 1; i >= 0; i--)
	{
		vector_2d_c intersect(0, 0);
		E_INTERSECTION intersect_type = line.get_intersection(this->get_line(i), intersect);

		if(intersect_type == EI_SEGMENT)
		{
			return(intersect);
		}
	}

	return(vector_2d_c(0, 0));
}


airfoil_c airfoil_c::get_circle_projection(uint32_t n, const vector_2d_c & projection_center) const
{
	std::vector<vector_2d_c> newpoints;

	for(unsigned int i = 0; i < n; i++)
	{
		vector_2d_c circle_point = vector_2d_radian(0.5, (M_PI * i) / n) + vector_2d_c(0.5, 0);
		vector_2d_c inverse_point = vector_2d_c(circle_point.x, -circle_point.y);
		newpoints.push_back(this->get_intersection_first(line_2d_c(circle_point, inverse_point)));
	}

	for(unsigned int i = n; i < 2 * n; i++)
	{
		vector_2d_c circle_point = vector_2d_radian(0.5, (M_PI * i) / n) + vector_2d_c(0.5, 0);
		vector_2d_c inverse_point = vector_2d_c(circle_point.x, -circle_point.y);
		newpoints.push_back(this->get_intersection_last(line_2d_c(circle_point, inverse_point)));
	}

	return(airfoil_c(newpoints));
}






} //namespace wif_core
