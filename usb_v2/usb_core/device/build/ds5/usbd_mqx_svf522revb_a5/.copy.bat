@echo off
set FROM=%1
set FROM=%FROM:/=\%
set TO=%2
set TO=%TO:/=\%
copy "%FROM%" "%TO%" /Y
