#ifndef __AIRFOIL_C_HPP_INCLUDED__
#define __AIRFOIL_C_HPP_INCLUDED__

#include <string>
#include <vector>
#include "line_2d_c.hpp"



namespace wif_core
{



class airfoil_c
{
public:
	/**
	 * Lege constructor: zonder points
	 */
	airfoil_c();

	/**
	 * Leest de file in filename, laat points leeg als er iets misloopt. Moet beiden .dat formaten kunnen lezen.
	 * name wordt gelijk gesteld aan de naam die binnen de file staat.
	 */
	airfoil_c(const std::string & filename);

	/**
	 * Naam is name
	 */
	airfoil_c(std::vector<vector_2d_c> & points, const std::string & name);

	/**
	 * Naam nieuwe airfoil is oude naam + " circle projected with $n subdivisions centered on $projection_center with radius $radius".
	 */
	airfoil_c get_circle_projection(uint32_t n, const vector_2d_c & projection_center, double radius) const;

	/**
	 * Is het laatste punt hetzelfde als de eerste, dan is de curve gesloten. De epsilon dient voor
	 * floating point weirdness met afrondingen tegen te gaan.
	 */
	bool is_closed(double epsilon = 0.0001) const;

	/**
	 * Zit er ten minste 1 punt in de vector (handig als tijdens het lezen iets misloopt).
	 */
	bool is_valid() const;

	/**
	 * Maakt van alle koppels ([i], [i+1]) lijnstukken, met i = 0 tot i < points.size()-1.
	 */
	std::vector<line_2d_c> get_lines() const;

	/**
	 * Hetzelfde als get_lines, maar de lijnstukken worden in omgekeerde volgorde weergegeven,
	 * (merk op dat begin en end nog wel dezelfde waarden hebben)
	 */
	std::vector<line_2d_c> get_lines_reversed() const;


	/**
	 * Geeft de naam.
	 */
	std::string get_name() const;

	void set_name(const std::string & new_name);

private:
	/**
	 * returns first intersection with line
	 */
	vector_2d_c get_intersection_last(const line_2d_c line) const;

	/**
	 * returns last intersection with line
	 */
	vector_2d_c get_intersection_first(const line_2d_c line) const;




private:
	std::vector<vector_2d_c> points;
	std::string name;

};






} // namespace wif_core

#endif // __AIRFOIL_C_HPP_INCLUDED__
