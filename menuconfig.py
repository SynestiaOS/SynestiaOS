#!/usr/bin/env python3

import os

if __name__ == '__main__':
    here = os.path.dirname(os.path.abspath(__file__))

    os.chdir(here)

    from KconfigLib import menuconfig

    # noinspection PyProtectedMember
    menuconfig._main()
