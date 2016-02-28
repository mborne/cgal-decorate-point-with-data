#include <iostream>


#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Decorate_point_with_data.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Cartesian ;
typedef CGAL::Exact_predicates_exact_constructions_kernel Epeck ;
typedef CGAL::Exact_predicates_exact_constructions_kernel Epick ;

typedef CGAL::Decorate_point_with_data< Cartesian::FT, double > CartesianM;
typedef CGAL::Decorate_point_with_data< Epeck::FT, double > EpeckM;
typedef CGAL::Decorate_point_with_data< Epick::FT, double > EpickM;

//typedef CGAL::Decorate_point_with_data< Epick, double > EpickM;

int main( int argc, char* argv[] ){
    CGAL::Point_2< EpickM > a(3.0,4.0);
    a.data() = 15.0 ;
    std::cout << a << " (M=" << a.data() << ")" << std::endl;
    return 0 ;
}
