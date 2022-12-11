#!/bin/bash
sops -d secrets.enc.h > secrets.h
