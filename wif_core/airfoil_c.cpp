#include "airfoil_c.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <assert.h>

#include <iterator>
#include <sstream>



namespace wif_core
{


airfoil_c::airfoil_c() :
	name("")
{
	//
}


airfoil_c::airfoil_c(const std::string & filename)
{

	std::ifstream detect(filename);

	if(!detect.is_open())
	{
		return; //just give up if file does not open
	}

	std::string line1;
	std::string data_pit;
	std::getline(detect, line1);
	double testval;
	detect >> testval;
	std::cout << "testvalue :" << testval << std::endl;
	detect.close();
	std::ifstream data(filename);

	if(!data.is_open())
	{
		return; //just give up if file does not open
	}


	if(testval > 1)
	{

		std::getline(data, this->name);
		std::getline(data, data_pit);

		while(data.good())
		{
			double x;
			double y;
			data >> x >> y;
			this->points.emplace_back(x, y);
			//std::cout << x << "\t" << y << std::endl;
		}

		unsigned int half_size = this->points.size() / 2;
		std::reverse(this->points.begin() + half_size, this->points.end());
	}
	else
	{

		//selig format
		std::getline(data, this->name);

		while(data.good())
		{
			double x;
			double y;
			data >> x >> y;
			this->points.emplace_back(x, y);
			//std::cout << x << "\t" << y << std::endl;
		}
	}

	this->points.pop_back(); //reads last line double. Not any more

}

airfoil_c::airfoil_c(std::vector<vector_2d_c> & points, const std::string & name) :
	name(name),
	points(points)
{
	//
}


airfoil_c::airfoil_c(const vector_2d_c & midpoint, double radius, unsigned int corners) :
	name("circle")
{
	for(unsigned int i = 0; i <= corners; i++)
	{
		points.push_back(vector_2d_radian(radius, (2 * M_PI * i) / corners) + midpoint);
	}
}


std::vector<line_2d_c> airfoil_c::get_lines() const
{
	std::vector<line_2d_c> ret;

	for(unsigned int index = 0; index < this->points.size() - 1; index++)
	{

		line_2d_c r(this->points[index], this->points[index + 1]);
		ret.push_back(r);

	}

	return ret;
}


const std::vector<vector_2d_c> & airfoil_c::get_points() const
{
	return points;
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
	return (this->points.front() - this->points.back()).get_length_sq() < (epsilon * epsilon);
}


airfoil_c airfoil_c::closed_merge(double epsilon) const
{
	if(this->is_closed(epsilon) or !this->is_valid())
	{
		return *this;
	}

	vector_2d_c endpoint = (points.front() + points.back()) / 2;
	std::vector<vector_2d_c> newpoints;
	newpoints.push_back(endpoint);
	newpoints.insert(newpoints.end(), this->points.begin() + 1, this->points.end() - 1);
	newpoints.push_back(endpoint);

	std::stringstream newname;
	newname << this->name << " closed";
	return airfoil_c(newpoints, newname.str());
}

airfoil_c airfoil_c::closed_intersect(double epsilon) const
{
	if(this->is_closed(epsilon) or !this->is_valid())
	{
		return *this;
	}

	vector_2d_c endpoint;
	this->get_lines().front().get_intersection(this->get_lines().back(), endpoint);
	std::vector<vector_2d_c> newpoints;
	newpoints.push_back(endpoint);
	newpoints.insert(newpoints.end(), this->points.begin(), this->points.end());
	newpoints.push_back(endpoint);

	std::stringstream newname;
	newname << this->name << " closed";
	return airfoil_c(newpoints, newname.str());
}


bool airfoil_c::is_valid() const
{
	return this->points.size() > 1;
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

	return output;
};


} //namespace wif_core
