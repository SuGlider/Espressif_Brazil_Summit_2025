idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
# this project depends on the my_blink private IDF component we created as example 
# for using both a regular IDF Component and Arduino API as IDF Component in the same code
    REQUIRES my_blink
)
