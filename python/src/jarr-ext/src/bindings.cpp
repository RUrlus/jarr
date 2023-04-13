#include <pybind11/pybind11.h>
#include <jarr/main.hpp>

namespace py = pybind11;

namespace jarr {

PYBIND11_MODULE(_jarr_ext, m) {
  bind_add(m);
  bind_arange(m);
}

}  // namespace jarr
