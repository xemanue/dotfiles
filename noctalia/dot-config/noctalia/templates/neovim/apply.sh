#!/usr/bin/env bash
pkill -SIGUSR1 nvim >/dev/null 2>&1 || true
