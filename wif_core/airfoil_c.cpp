#include "airfoil_c.hpp"

#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace wif_core
{


airfoil_c::airfoil_c() :
	name("")
{
	//
}


airfoil_c::airfoil_c(const std::string & filename)
{
	//selig format
	std::ifstream detect(filename);
	std::string line1;
	std::string line2;
	std::string line3;
	std::getline(detect, line1);
	std::getline(detect, line2);
	std::getline(detect, line3);
	std::cout << line1 << std::endl;
	std::cout << line2 << std::endl;
	std::cout << line3 << std::endl;
	detect.close();
	std::ifstream data(filename);

	if(line3.empty())
	{
		//

		double len1;
		double len2;
		std::string data_pit;
		std::getline(data, this->name);
		std::getline(data, data_pit);

		while(!data.eof())
		{
			double x;
			double y;
			data >> x >> y;
			this->points.push_back(vector_2d_c(x, y));
		}

		unsigned int half_size = this->points.size() / 2;
		std::reverse(this->points.begin() + half_size, this->points.end());
	}
	else
	{
		//selig format

		std::getline(data, this->name);

		while(!data.eof())
		{
			double x;
			double y;
			data >> x >> y;
			this->points.push_back(vector_2d_c(x, y));
		}
	}
}


airfoil_c::airfoil_c(std::vector<vector_2d_c> & points, const std::string & name) :
	name(name)
{
	this->points.resize(points.size());
	copy(points.begin(), points.end(), this->points.begin());
}


std::vector<line_2d_c> airfoil_c::get_lines() const
{
	std::vector<line_2d_c> ret;

	for(unsigned int index = 0; index < this->points.size(); index++)
	{
		if(index == this->points.size() - 1)
		{
			line_2d_c r(this->points[this->points.size() - 1], this->points[0]);
			ret.push_back(r);
		}
		else
		{
			line_2d_c r(this->points[index], this->points[index + 1]);
			ret.push_back(r);
		}
	}

	return ret;
}


std::vector<line_2d_c> airfoil_c::get_lines_reversed() const
{
	std::vector<line_2d_c> ret = this->get_lines();
	std::reverse(ret.begin(), ret.end());
	return ret;
}


vector_2d_c airfoil_c::get_intersection_first(const line_2d_c & line) const
{
	for(line_2d_c l : this->get_lines())
	{
		vector_2d_c intersect(0, 0);
		E_INTERSECTION intersect_type = line.get_intersection(l, intersect);

		if(intersect_type == EI_SEGMENT)
		{
			return(intersect);
		}
	}

	return line.get_center_point() ;
}


vector_2d_c airfoil_c::get_intersection_last(const line_2d_c & line) const
{
	for(line_2d_c l : this->get_lines_reversed())
	{
		vector_2d_c intersect(0, 0);
		E_INTERSECTION intersect_type = line.get_intersection(l, intersect);

		if(intersect_type == EI_SEGMENT)
		{
			return(intersect);
		}
	}

	return line.get_center_point() ;
}


airfoil_c airfoil_c::get_circle_projection(uint32_t n, const vector_2d_c & projection_center, double radius, double epsilon) const
{
	std::vector<vector_2d_c> newpoints;
	std::stringstream newname;

	for(unsigned int i = 0; i < n; i++)
	{
		vector_2d_c circle_point = vector_2d_radian(radius, (M_PI * i) / n) + projection_center;
		vector_2d_c top_point = vector_2d_c(circle_point.x, 1);
		vector_2d_c inverse_point = vector_2d_c(circle_point.x, -1);
		line_2d_c vert_line(top_point, inverse_point);
		vector_2d_c intersect = this->get_intersection_first(vert_line);
		newpoints.push_back(intersect);
	}

	for(unsigned int i = n; i < 2 * n; i++)
	{
		vector_2d_c circle_point = vector_2d_radian(radius, (M_PI * i) / n) + projection_center;
		vector_2d_c top_point = vector_2d_c(circle_point.x, 1);
		vector_2d_c inverse_point = vector_2d_c(circle_point.x, -1);
		line_2d_c vert_line(top_point, inverse_point);
		vector_2d_c intersect = this->get_intersection_first(vert_line);
		newpoints.push_back(intersect);
	}


	newname << this->name << " circle projected with " << n << " subdivisions centered on " << projection_center;


	return airfoil_c(newpoints, newname.str());
}


bool airfoil_c::is_closed(double epsilon) const
{
	return((this->points.front() - this->points.back()).get_length_sq() < pow(epsilon, 2));
}


bool airfoil_c::is_valid() const
{
	return not this->points.empty();
}


std::string airfoil_c::get_name() const
{
	return this->name;
}


void airfoil_c::set_name(const std::string & new_name)
{
	this->name = new_name;
}


std::ostream & operator << (std::ostream & output, const airfoil_c & airfoil)
{
	output << airfoil.name << std::endl;

	for(vector_2d_c v : airfoil.points)
	{
		output << v.x << "\t" << v.y << std::endl;
	}
};


} //namespace wif_core
