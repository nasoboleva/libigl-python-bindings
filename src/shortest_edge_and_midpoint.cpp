#include <npe.h>
#include <typedefs.h>






#include <igl/shortest_edge_and_midpoint.h>

const char* ds_shortest_edge_and_midpoint = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Cost and placement function compatible with igl::decimate. The cost of
   collapsing an edge is its length (prefer to collapse short edges) and the
   placement strategy for the new vertex is the midpoint of the collapsed
   edge.

   Inputs:
     e  index into E of edge to be considered for collapse
     V  #V by dim list of vertex positions
     F  #F by 3 list of faces (ignored)
     E  #E by 2 list of edge indices into V
     EMAP  #F*3 list of half-edges indices into E (ignored)
     EF  #E by 2 list of edge-face flaps into F (ignored)
     EI  #E by 2 list of edge-face opposite corners (ignored)
   Outputs:
     cost  set to edge length
     p  placed point set to edge midpoint
)igl_Qu8mg5v7";

npe_function(shortest_edge_and_midpoint)
npe_doc(ds_shortest_edge_and_midpoint)

npe_arg(edge, int)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(e, npe_matches(f))
npe_arg(emap, Eigen::VectorXi &)

npe_arg(ef, npe_matches(f))
npe_arg(ei, npe_matches(f))

npe_arg(cost, double)
npe_arg(p, Eigen::RowVectorXd &)

npe_begin_code()

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();

  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::VectorXi emap_copy = emap.template cast<int>();

  Eigen::MatrixXi ef_copy = ef.template cast<int>();
  Eigen::MatrixXi ei_copy = ei.template cast<int>();

  Eigen::RowVectorXd & p_copy = p;
  double & cost_copy = cost;
  igl::shortest_edge_and_midpoint(edge, v_copy, f_copy, e_copy, emap_copy, ef_copy, ei_copy, cost_copy, p_copy);
  return std::make_tuple(cost_copy, npe::move(p_copy));

npe_end_code()

