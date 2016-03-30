# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess

@given(u'I start streetlightd')
def step_impl(context):
	context.proc = subprocess.Popen(['streetlightd'])

