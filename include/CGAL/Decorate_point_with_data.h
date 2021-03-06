/*
 * WARNING : 
 * - This file is not (yet?) part of CGAL library.
 * - The code is not clean enougth to be use in production
 * 
 * @author Mickaël BORNE (IGN France) 2016
 * Licence LGPL
 */
#ifndef CGAL_DECORATE_POINT_WITH_DATA_H_
#define CGAL_DECORATE_POINT_WITH_DATA_H_

#include <CGAL/Cartesian.h>

namespace CGAL {
    
    /**
     * Decorated point 2
     */
    template < typename OldKernel, typename DataType >
    class Point_2_with_data : private OldKernel::Point_2 {
    public:
        typedef typename OldKernel::Point_2 Old_point_2 ;
        typedef typename OldKernel::RT   RT ;
        typedef typename OldKernel::FT   FT ;
        
        using Old_point_2::Old_point_2;
        
        using Old_point_2::x;
        using Old_point_2::y;

        DataType & data() { return _data ; }
        const DataType & data() const { return _data ; }
    private:
        DataType         _data ;
    } ;


    // Adapter from cgal/Arrangement_on_surface_2/test/Arrangement_on_surface_2/ex_kernel_point.cpp
    template <typename K, typename OldK> 
    class Construct_point_2_with_data {
        typedef typename K::RT              RT;
        typedef typename K::Point_2         Point_2;
        typedef typename K::Line_2          Line_2;
        typedef typename Point_2::Rep       Rep;
    public:
        typedef Point_2                     result_type;

        // Note : the CGAL::Return_base_tag is really internal CGAL stuff.
        // Unfortunately it is needed for optimizing away copy-constructions,
        // due to current lack of delegating constructors in the C++ standard.
        Rep // Point_2
        operator()(CGAL::Return_base_tag, CGAL::Origin o) const
        { return Rep(o); }

        Rep // Point_2
        operator()(CGAL::Return_base_tag, const RT& x, const RT& y) const
        { return Rep(x, y); }

        Rep // Point_2
        operator()(CGAL::Return_base_tag, const RT& x, const RT& y, const RT& w) const
        { return Rep(x, y, w); }

        // End of hell

        Point_2 operator()(CGAL::Origin o) const
        { return result_type(0,0,0); }
    
        
        Point_2 operator()(const RT & x, const RT & y) const
        { 
            return result_type(x, y, 1); // TODO fix why 0 in the example
        }

        Point_2 operator()(const Line_2 & l) const
        {
            typename OldK::Construct_point_2 base_operator;
            Point_2 p = base_operator(l);
            return p;
        }

        Point_2 operator()(const Line_2 & l, int i) const
        {
            typename OldK::Construct_point_2 base_operator;
            return base_operator(l, i);
        }

        // We need this one, as such a functor is in the Filtered_kernel
        Point_2 operator()(const RT & x, const RT & y, const RT & w) const
        {
            if(w != 1) {
                return result_type(x/w, y/w, 0); 
            } else {
                return result_type(x,y, 0);
            }
        }
    };


    // Kernel is the new kernel, and Kernel_base is the old kernel
    template <typename Kernel, typename Kernel_base, typename UserData >
    class Decorate_point_with_data_base : public Kernel_base::template Base<Kernel>::Type {
    public:
        typedef typename Kernel_base::template Base<Kernel>::Type     Old_kernel;
        typedef typename Old_kernel::Point_2                          Old_point_2;
        typedef typename Old_kernel::FT                               FT;
        typedef typename Old_kernel::RT                               RT;
        typedef typename Old_kernel::Segment_2                        Segment_2;  

    public:
        typedef Point_2_with_data<Old_kernel, UserData>               Point_2;
        typedef Construct_point_2_with_data<Kernel, Old_kernel>       Construct_point_2;

        Construct_point_2 construct_point_2_object() const
        { return Construct_point_2(); }

        template <typename Kernel2>
        struct Base { 
            typedef Decorate_point_with_data_base<Kernel2, Kernel_base, UserData> Type; 
        };
    };
    
    
    /*! The extended Kernel type */
    template <typename FT_, typename DataType>
    struct Decorate_point_with_data : public CGAL::Type_equality_wrapper<
        Decorate_point_with_data_base<
            Decorate_point_with_data<FT_,DataType>,
            CGAL::Cartesian<FT_>,
            DataType
        >,
        Decorate_point_with_data<FT_,DataType> 
    >{};

    
} // SFCGAL


#endif
