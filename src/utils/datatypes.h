
#ifndef NIX_MX_DATATYPES_H
#define NIX_MX_DATATYPES_H

#include <nix/DataType.hpp>
#include <mex.h>

inline nix::DataType dtype_mex2nix(const mxArray *array) {
	mxClassID cid = mxGetClassID(array);
	
	switch (cid) {
	case mxLOGICAL_CLASS: return nix::DataType::Bool;

	case mxCHAR_CLASS:   return nix::DataType::String;

	case mxDOUBLE_CLASS: return nix::DataType::Double;
	case mxSINGLE_CLASS: return nix::DataType::Float;

	case mxUINT8_CLASS:  return nix::DataType::UInt8;
	case mxINT8_CLASS:   return nix::DataType::Int8;
	case mxUINT16_CLASS: return nix::DataType::UInt16;
	case mxINT16_CLASS:  return nix::DataType::Int16;
	case mxUINT32_CLASS: return nix::DataType::UInt32;
	case mxINT32_CLASS:  return nix::DataType::Int32;
	case mxUINT64_CLASS: return nix::DataType::UInt64;
	case mxINT64_CLASS:  return nix::DataType::Int64;

#ifndef HAVE_OCTAVE
		case mxOPAQUE_CLASS: return nix::DataType::Opaque;
#endif
	default:             return nix::DataType::Nothing;
	}

}

//DType^2, the type of the DataType
struct DType2 {
	mxClassID    cid;
	mxComplexity clx;
	bool         is_valid;
};

inline DType2 dtype_nix2mex (nix::DataType dtype) {
	DType2 dt;
	dt.clx = mxREAL;
	dt.is_valid = true;

	switch (dtype) {
	case nix::DataType::Bool: dt.cid = mxLOGICAL_CLASS; break;

	case nix::DataType::String: dt.cid = mxCHAR_CLASS; break;

	case nix::DataType::Float: dt.cid = mxSINGLE_CLASS; break;
	case nix::DataType::Double: dt.cid = mxDOUBLE_CLASS; break;

	case nix::DataType::UInt8: dt.cid = mxUINT8_CLASS; break;
	case nix::DataType::UInt16: dt.cid = mxUINT16_CLASS; break;
	case nix::DataType::UInt32: dt.cid = mxUINT32_CLASS; break;
	case nix::DataType::UInt64: dt.cid = mxUINT64_CLASS; break;

	case nix::DataType::Int8: dt.cid = mxINT8_CLASS; break;
	case nix::DataType::Int16: dt.cid = mxINT16_CLASS; break;
	case nix::DataType::Int32: dt.cid = mxINT32_CLASS; break;
	case nix::DataType::Int64: dt.cid = mxINT64_CLASS; break;

	default: dt.is_valid = false;
	}

	return dt;
}

inline std::string string_nix2mex(nix::DataType dtype) {
    std::string dt;

    switch (dtype) {
    case nix::DataType::Bool: dt = "logical"; break;
    case nix::DataType::String: dt = "char"; break;
    case nix::DataType::Float: dt = "single"; break;

    default: dt = nix::data_type_to_string(dtype);
    }

    std::transform(dt.begin(), dt.end(), dt.begin(), ::tolower);

    return dt;
}

#endif