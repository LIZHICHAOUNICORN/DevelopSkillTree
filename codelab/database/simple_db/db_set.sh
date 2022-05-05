#!/bin/bash
db_set () {
    echo "set key: $1 value: $2"
    echo "$1,$2" >> database
}
db_set $1 $2
