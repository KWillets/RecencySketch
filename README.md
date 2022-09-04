# RecencySketch
RecencySketch is an approximate data structure which estimates, for an a-priori unknown set of keys, the last time that a given key was seen. Like a Bloom Filter or Count-Min sketch, it has a one-sided error; it will never report a value older than the true value, but it can report a later or more recent one. This error behavior may be beneficial in cases which we will discuss below.

To update the sketch for a given (key,timestamp) pair, the key is hashed to select an index within an array of timestamp values. If the input timestamp is later than the element currently at the selected index, that element is set to the input. This process may be repeated with multiple hash functions and arrays similar to a Count-min sketch.

To read the sketch, the input key is hashed, the corresponding array elements are selected, and the minimum (earliest) value is returned as the estimate. If the key has not had collisions since it was last seen, the true time for that event will be returned. If collisions occur, a more recent time may be returned.

## Usage Scenarios
### Request Pacing
This sketch may be used to ensure a minimum latency between granted requests (ie a maximum frequency) for a service such as packet forwarding, API response, or asset usage. Given an indefinite sequence of requests, a service can use this sketch to estimate for each requestor R, when the last request from R was granted, and whether enough time has passed for its request to be granted again. 

In the case of a collision, the sketch may incorrectly report a later last-granted time. A key may therefore experience expanding latency between granted requests, but each request will have a fair chance versus other colliding keys.

A useful property of this failure mode is that even with an unbounded keyspace the total request grant rate will approach a constant, as each array element can allow only one request per L regardless of collisions. The sketch can therefore be sized to keep delivery rate below the maximum capacity of the service.

### Time-based Caching
For TTL-based cache, approximate recency can serve as a filter before querying the cache itself, to avoid querying an expired item. The reported insertion time will never be before the actual, but if a collision sets a later time the cache may be incorrectly queried for an expired item. The asymptotic failure state is to query the cache unconditionally, as if the filter does not exist, so it is fail-safe in that way.

The value stored in the sketch can be either insertion time or the calculated expiration time (insertion time + TTL); the latter method encodes the TTL if it is supplied at insertion time (eg with memcached).
