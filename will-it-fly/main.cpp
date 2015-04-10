#include <iostream>

#include <wif-core/wif_core.hpp>
#include <wif-algo/wif_algo.hpp>
#include <wif-viz/wif_viz.hpp>

int main(){

    std::cout << wif_core::get_version();
    std::cout << wif_algo::get_version();
    std::cout << wif_viz::get_version();

}
