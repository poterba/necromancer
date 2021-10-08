/**
 * GreenPois0n Apparition - mbdb.h
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 Joshua Hill
 * Copyright (C) 2012 Hanéne Samara
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#pragma once

#include "mbdb_record.hpp"

#define MBDB_MAGIC "\x6d\x62\x64\x62\x05\x00"

namespace absinthe
{
namespace backup
{

class MBDB final
{
public:
    void open(unsigned char* file);
    void parse(unsigned char* data, unsigned int size);
    mbdb_record::mbdb_record_t* get_record(unsigned int offset);

private:
    unsigned int size;
    unsigned char* data;

    struct header
    {
        unsigned char magic[6]; // 'mbdb\5\0'
    };
    header_t* header;
    int num_records;
    mbdb_record::mbdb_record_t** records;
}

extern MBDB* apparition_mbdb;

} // namespace mbdb
} // namespace backup
} // namespace absinthe
