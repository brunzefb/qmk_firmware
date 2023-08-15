#!/bin/bash
sops -e secrets.h > secrets.enc.h
