#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <pybind11/stl.h>

#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(
See collapse_edge for the documentation.
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(edge, int)
npe_arg(p, Eigen::RowVectorXd &)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(e, npe_matches(f))
npe_arg(emap, Eigen::VectorXi &)

npe_arg(ef, npe_matches(f))
npe_arg(ei, npe_matches(f))

npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  Eigen::MatrixXd v_copy = v.template cast<double>();

  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXi e_copy = e.template cast<int>();
  Eigen::VectorXi emap_copy = emap.template cast<int>();

  Eigen::MatrixXi ef_copy = ef.template cast<int>();
  Eigen::MatrixXi ei_copy = ei.template cast<int>();

  igl::collapse_edge(edge, p, v_copy, f_copy, e_copy, emap_copy, ef_copy, ei_copy);

  EigenDenseLike<npe_Matrix_v> v_r = v_copy.template cast < typename npe_Matrix_v::Scalar >();
  EigenDenseLike<npe_Matrix_f> f_r = f_copy.template cast<typename npe_Matrix_f::Scalar>();
  EigenDenseLike<npe_Matrix_f> e_r = e_copy.template cast<typename npe_Matrix_f::Scalar>();

  EigenDenseLike<npe_Matrix_f> ef_r = ef_copy.template cast<typename npe_Matrix_f::Scalar>();
  EigenDenseLike<npe_Matrix_f> ei_r = ei_copy.template cast<typename npe_Matrix_f::Scalar>();

  return std::make_tuple(npe::move(v_r), npe::move(f_r), npe::move(e_r), npe::move(emap_copy), npe::move(ef_r), npe::move(ei_r));

npe_end_code()