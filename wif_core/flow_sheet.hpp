#ifndef FLOW_SHEET_HPP_INCLUDED
#define FLOW_SHEET_HPP_INCLUDED

#include "line_2d_c.hpp"
#include "vector_2d_c.hpp"

namespace wif_core
{

class flow_sheet
{
	public:
		flow_sheet(const line_2d_c &);
		virtual ~flow_sheet();
		flow_sheet(const flow_sheet& other);
		flow_sheet& operator=(const flow_sheet& other);

		/**
		 * gives the streamfunction at a given point
		 * allways type 'using flow_sheet::psi(vector_2d_c) const' in derived classes
		*/
		double psi(const vector_2d_c&) const;
		double psi(double,double) const;

		/**
		 * the function that should be integrated from 0 to 1 to
		 * get psi
		*/
		double psi_for_integration(double,const vector_2d_c&) const;

		/**
		 * the effect of an source,vortex,... on pos1 on psi in pos2
		 * should be implemented in derived classes
		*/
		virtual double psi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const =0;

		/**
		 * gives the streampotential at a given point
		*/
		double phi(const vector_2d_c&) const;
		double phi(double,double) const;

		/**
		 * the function that should be integrated from 0 to 1 to
		 * get phi
		*/
		double phi_for_integration(double,const vector_2d_c&) const;

		/**
		 * the effect of an source,vortex,... on pos1 on phi in pos2
		 * should be implemented in derived classes
		*/
		virtual double phi_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const =0;

		/**
		 * gives the velocity
		 * allways type 'using flow_sheet::v(vector_2d_c) const' in derived classes
		*/
		vector_2d_c v(const vector_2d_c&) const;
		vector_2d_c v(double,double) const;

		/**
		 * the function that should be integrated from 0 to 1 to
		 * get v
		*/
		vector_2d_c v_for_integration(double,const vector_2d_c&) const;

		/**
		 * the effect of an source,vortex,... on pos1 on v in pos2
		 * should be implemented in derived classes
		*/
		virtual vector_2d_c v_one_point(const vector_2d_c& pos1,const vector_2d_c& pos2) const =0;

		/**
		 * gives a point on line corresponding to the
		 * parameter t
		*/
		vector_2d_c line_equation(double t) const;

		line_2d_c line;
	protected:
	private:
};

}

#endif // FLOW_SHEET_HPP_INCLUDED
