#ifndef ERRORCODE_HPP_
#define ERRORCODE_HPP_

/* MESSAGE (STRING) */
#define BAD_ARGUMENT "Bad arguments. The arguments must be the path of the configuration's file.\n"
#define BAD_CONFIG "Bad configuration."
#define BAD_FILE "The file is not found."
#define BAD_PARSING "Error during the parsing of the json file provided."
#define BAD_LIFE_MIN "'life-min' must be an integer between 0 and 8. By default it is set on 2."
#define BAD_LIFE_MAX "'life-max' must be an integer between 0 and 8. By default it is set on 3."
#define BAD_REPRO_MIN "'repro-min' must be an integer between 0 and 8. By default it is set on 3."
#define BAD_REPRO_MAX "'repro-max' must be an integer between 0 and 8. By default it is set on 3."
#define BAD_COLORFUL_GRID "'colorful-grid' must be a boolean. By default it is set on false."
#define BAD_START_STATE "'start-state' must be an array not empty."
#define BAD_START_STATE_CASE "Each object of the 'start-state' must have the following values 'x', 'y', 'population'."

/* CODE (INTEGER) */
#define ERROR_CODE -1


#endif // ERRORCODE_HPP_