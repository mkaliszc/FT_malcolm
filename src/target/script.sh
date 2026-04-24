#!/bin/sh
until ping -c1 172.20.0.2 > /dev/null 2>&1; 
	do sleep 1; 
done && ./target AA:BB:CC:DD:EE:03 FF:FF:FF:FF:FF:FF 172.20.0.3 172.20.0.5