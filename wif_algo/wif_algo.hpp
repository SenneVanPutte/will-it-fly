#ifndef __WIF_ALGO_HPP_INCLUDED__
#define __WIF_ALGO_HPP_INCLUDED__

#include <cstdint>
#include <memory>
#include <iostream>
#include <numeric>
#include <stdio.h>
#include <memory>
#include <cmath>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_integration.h>
#include <wif_core/wif_core.hpp>

namespace wif_algo
{

struct calculation_results_c
{
	/// Een kopie van de input airfoil
	wif_core::airfoil_c airfoil;

	/// Een flowobject dat eruit komt.
	std::shared_ptr<wif_core::flow_c> flow;

	/// c_p[i] moet overeenkomen met panel airfoil.get_lines()[i]
	std::vector<double> c_p;
	double c_l;
};

uint32_t get_version();

/// Het toevoegen van extra parameters aan deze functie mag, zodat mensen kunnen selecteren of ze de Kutta Conditie enzo willen gebruiken.
calculation_results_c calculate_flow(const wif_core::airfoil_c & myAirfoil, std::shared_ptr<wif_core::uniform_flow_c> myFlow, bool Kutta = false);
std::vector<double> calculate_c_p(const wif_core::airfoil_c & myAirfoil, std::shared_ptr<wif_core::uniform_flow_c> myFlow, double gamma = 0);
} // namespace wif_algo

#endif // __WIF_ALGO_HPP_INCLUDED__
