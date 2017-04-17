./tests/tests
lcov --capture --directory tests/ --output-file coverage.info
genhtml coverage.info --output-directory out
google-chrome out/index.html

