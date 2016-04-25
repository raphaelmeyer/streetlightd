# -*- coding: utf-8 -*-

# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

def intToHex(value):
	symbols = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
	return symbols[(value >> 4) & 0xf] + symbols[value & 0xf]

def bytesToString(value):
	return ' '.join(map(intToHex, value))

def hexToInt(value):
	return int(value, 16)

def stringToBytes(value):
	return bytearray(map(hexToInt, value.split()))

