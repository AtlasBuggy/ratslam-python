#include "ExperienceStructWrapper.hpp"


PyExperience::PyExperience(Experience experience_struct)
{
    this->experience_struct = &experience_struct;
}

object PyExperience::id() {
    return object(this->experience_struct->id);
}

object PyExperience::x_m() {
    return object(this->experience_struct->x_m);
}

object PyExperience::y_m() {
    return object(this->experience_struct->y_m);
}

object PyExperience::th_rad() {
    return object(this->experience_struct->th_rad);
}

object PyExperience::x_pc() {
    return object(this->experience_struct->x_pc);
}

object PyExperience::y_pc() {
    return object(this->experience_struct->y_pc);
}

object PyExperience::th_pc() {
    return object(this->experience_struct->th_pc);
}

tuple PyExperience::links_from() {
    // object get_iter = boost::python::iterator<std::vector<T> >();
    // object iter = get_iter(this->experience_struct->links_from);
    // tuple t(iter);
    //
    // return t;
    return tuple(this->experience_struct->links_from);
}

tuple PyExperience::links_to() {
    // object get_iter = boost::python::iterator<std::vector<T> >();
    // object iter = get_iter(this->experience_struct->links_to);
    // tuple t(iter);
    //
    // return t;
    return tuple(this->experience_struct->links_to);
}
