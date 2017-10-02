#include <boost/python.hpp>
#include <Ratslam.hpp>
#include <Experience_Map.h>

using namespace boost::python;
using namespace ratslam;

class PyExperience
{
public:
    PyExperience(Experience exp);

    object id();
    object x_m();
    object y_m();
    object th_rad();
    object x_pc();
    object y_pc();
    object th_pc();
    tuple links_from();
    tuple links_to();
private:
    Experience *exp;
};

PyExperience::PyExperience(Experience exp)
{
    this->exp = &exp;
}

object PyExperience::id() {
    return object(exp->id);
}

object PyExperience::x_m() {
    return object(exp->x_m);
}

object PyExperience::y_m() {
    return object(exp->y_m);
}

object PyExperience::th_rad() {
    return object(exp->th_rad);
}

object PyExperience::x_pc() {
    return object(exp->x_pc);
}

object PyExperience::y_pc() {
    return object(exp->y_pc);
}

object PyExperience::th_pc() {
    return object(exp->th_pc);
}

tuple PyExperience::links_from()
{
    object get_iter = iterator<std::vector<int> >();
    object iter = get_iter(exp->links_from);
    tuple t(iter);
    return t;
}

tuple PyExperience::links_to()
{
    object get_iter = iterator<std::vector<int> >();
    object iter = get_iter(exp->links_to);
    tuple t(iter);
    return t;
}
