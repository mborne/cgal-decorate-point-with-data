#include <iostream>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Decorate_point_with_data.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Epeck ;
typedef CGAL::Exact_predicates_exact_constructions_kernel Epick ;

typedef CGAL::Decorate_point_with_data< Epeck::FT, double >     EpeckM;
typedef CGAL::Decorate_point_with_data< Epick::FT, double >     EpickM;

typedef CGAL::Point_2< EpeckM > Point_2 ;
typedef CGAL::Segment_2< EpeckM > Segment_2 ;

int main( int argc, char* argv[] ){

    Point_2 a(0.0,0.0);
    a.data() = 15.0 ;
    std::cout << "a : " << a << " (M=" << a.data() << ")" << std::endl;
    
    Point_2 b(1.0,1.0);
    b.data() = 18.0 ;
    std::cout << "b : " << b << " (M=" << b.data() << ")" << std::endl;    

    Segment_2 ab(a,b);
    std::cout << "ab.source().data() : "<< ab.source().data() << std::endl;
    
    Point_2 c(0.5,0.0);
    Point_2 d(0.5,1.0);
    Segment_2 cd(c,d);

    auto intersection = CGAL::intersection(ab,cd) ;
    if ( intersection ){
        Point_2 * p = boost::get< Point_2 >(&*intersection) ;
        if ( p ){
            std::cout << (*p) << std::endl;
            std::cout << "M sur intersection : " << (*p).data() << std::endl;
        }
    }else{
        std::cout << "no intersection" << std::endl;
    }

    return 0 ;
}
