#!/usr/bin/env bash

search=${1}

awk '{print $2,$3,$4}' moving_object_catalog/ADR4.dat | grep "${search}"