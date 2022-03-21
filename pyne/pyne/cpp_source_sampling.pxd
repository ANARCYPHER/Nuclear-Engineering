################################################
#                 WARNING!                     #
# This file has been auto-generated by xdress. #
# Do not modify!!!                             #
#                                              #
#                                              #
#                    Come on, guys. I mean it! #
################################################


from libcpp cimport bool as cpp_bool
from libcpp.string cimport string as std_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.map cimport map as cpp_map

cdef extern from "source_sampling.h" namespace "pyne":

    cdef cppclass AliasTable:
        # constructors
        AliasTable() except +
        AliasTable(cpp_vector[double]) except +

        # attributes
        cpp_vector[int] alias
        int n
        cpp_vector[double] prob

        # methods
        int sample_pdf() except +
        int sample_pdf(double) except +
        int sample_pdf(double, double) except +


cdef extern from "source_sampling.h" namespace "pyne":

    cdef cppclass SourceParticle:
        # constructors
        SourceParticle() except +
        SourceParticle(double, double, double, double, double, cpp_vector[int]) except +

        # attributes

        # methods
        double get_x() except +
        double get_y() except +
        double get_z() except +
        double get_e() except +
        double get_w() except +
        cpp_vector[int] get_cell_list() except +


cdef extern from "source_sampling.h" namespace "pyne":

    cdef cppclass Sampler:
        # constructors
        Sampler() except +
        Sampler(std_string) except +
        Sampler(std_string, std_string) except +
        Sampler(std_string, std_string, cpp_vector[double]) except +
        Sampler(std_string, std_string, cpp_vector[double], std_string) except +
        Sampler(std_string, std_string, cpp_vector[double], cpp_bool) except +
        Sampler(std_string, cpp_map[std_string, std_string], int) except +
        Sampler(std_string, cpp_map[std_string, std_string], cpp_vector[double], int) except +

        # attributes


        # methods
        SourceParticle particle_birth() except +
        SourceParticle particle_birth(cpp_vector[double]) except +
