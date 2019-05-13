#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SLEEP 20
#define BUILD_KEY "AAAABBBBCCCC"

/**
 * Trigger that enables extra Windows specific flags to make application more transparent,
 * it also might alert some anti-virus programs about suspicious activity.
 */
#define EXTRA_TRANSPARENCY 0

/**
 * Name of the actual file that contains logged information.
 */
#define OUTPUT_NAME ".cache"

/**
 * Value in milliseconds that is used as interval to write buffer to output file.
 */
#define INTERVAL 9000

#endif // CONSTANTS_H
