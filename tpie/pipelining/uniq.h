// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; eval: (progn (c-set-style "stroustrup") (c-set-offset 'innamespace 0)); -*-
// vi:set ts=4 sts=4 sw=4 noet :
// Copyright 2011, 2012, The TPIE development team
// 
// This file is part of TPIE.
// 
// TPIE is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// TPIE is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with TPIE.  If not, see <http://www.gnu.org/licenses/>

#ifndef __TPIE_PIPELINING_UNIQ_H__
#define __TPIE_PIPELINING_UNIQ_H__

#include <tpie/pipelining/pipe_segment.h>
#include <tpie/pipelining/pipe_base.h>
#include <tpie/pipelining/factory_helpers.h>
#include <tpie/file_stream.h>

namespace tpie {

namespace pipelining {

namespace bits {

template <typename dest_t>
struct count_consecutive_t : public pipe_segment {
	typedef uint64_t count_t;
	typedef typename dest_t::item_type::first_type item_type;

	inline count_consecutive_t(const dest_t & dest)
		: dest(dest)
		, current_count(0)
	{
		add_push_destination(dest);
		set_name("Count consecutive", PRIORITY_INSIGNIFICANT);
	}

	virtual void end() /*override*/ {
		pipe_segment::end();
		flush();
	}

	inline void push(const item_type & item) {
		if (current_count && item == item_buffer) {
			++current_count;
		} else {
			flush();
			item_buffer = item;
			current_count = 1;
		}
	}
private:
	inline void flush() {
		if (!current_count) return;
		dest.push(std::make_pair(item_buffer, current_count));
		current_count = 0;
	}
	dest_t dest;
	item_type item_buffer;
	count_t current_count;
};

struct any_type {
	template <typename T>
	inline any_type(const T &) {}
	template <typename T>
	inline any_type & operator=(const T &) {return *this;}
};

template <typename dest_t>
struct extract_first_t : public pipe_segment {
	typedef std::pair<typename dest_t::item_type, any_type> item_type;

	inline extract_first_t(const dest_t & dest) : dest(dest) {
		add_push_destination(dest);
	}

	inline void push(const item_type & item) {
		dest.push(item.first);
	}
private:
	dest_t dest;
};

} // namespace bits

inline pipe_middle<bits::pair_factory<factory_0<bits::count_consecutive_t>, factory_0<bits::extract_first_t> > >
pipeuniq() {
	return bits::pair_factory<factory_0<bits::count_consecutive_t>, factory_0<bits::extract_first_t> >
		(factory_0<bits::count_consecutive_t>(), factory_0<bits::extract_first_t>());
}

}

}

#endif
