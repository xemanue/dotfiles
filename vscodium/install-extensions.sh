#!/usr/bin/env bash

cat extensions.txt | xargs -n 1 codium --install-extension
