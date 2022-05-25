#!/bin/bash
socat TCP-LISTEN:31337,reuseaddr,fork EXEC:'./check_server.py'
