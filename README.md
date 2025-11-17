This program simulates a image compression pipeline with three threads:

Camera Thread: Generates frames and loads them into cache

Transformer Thread: Compresses frames using quantization/dequantization

Estimator Thread: Calculates Mean Squared Error (MSE) between original and compressed frames

Usage: ```58532418_58533440_58542922 [INTERVAL] [THREADS] [OPTION]...\n"
            "\t-h, --help\t\t display this help\n"
            "\t-v, --verbose\t\t show entered values\n"
            "\n"
            "The INTERVAL argument is an integer, specifying seconds to sleep.\n"
            "If unset or invalid, defaults to 2 seconds.\n"
            "\n"
            "The THREADS argument is an integer, specifying number of camera thread(s) spawned.\n"
            "If unset or invalid, defaults to 4 threads.\n"
            "\n"
            "Exit status:\n"
            "0\tif OK,\n"
            "1\tif problem occurs.\n"```
