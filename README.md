# RecencySketch
RecencySketch is an approximate data structure which estimates, for an a-priori unknown set of keys, the last time that a given key was seen. Like a Bloom Filter or Count-Min sketch, it has a one-sided error; it will never report a value older than the true value, but it can report a later or more recent one. This error behavior may be beneficial in cases which we will discuss below.

To update the sketch for a given (key,timestamp) pair, the key is hashed to select an index within an array of timestamp values. If the input timestamp is later than the element currently at the selected index, that element is set to the input. This process may be repeated with multiple hash functions and arrays similar to a Count-min sketch.

To read the sketch, the input key is hashed, the corresponding array elements are selected, and the minimum (earliest) value is returned as the estimate. If the key has not had collisions since it was last seen, the true time for that event will be returned. If collisions occur, a more recent time may be returned.

##Usage Scenarios
This sketch may be used to ensure minimum latency between request for a service such as packet forwarding, API response, or asset usage so that no requestor will dominate usage. Given an indefinite set of requestors, a service can use this sketch to estimate for each requestor R, when the last request from R occurred, and whether enough time has passed for R's request to be granted. 

In the case of a collision for key R, the sketch will report that not enough time has passed, ie it will overestimate the recency, and R will be denied until a later time, when it will have an equal chance versus colliding keys. As the keyspace expands, each single key R may experience longer latency between successful requests, but each request will have a fair chance versus other colliding keys.

A useful property of this failure mode is that even with an unbounded keyspace the total request delivery rate will approach a constant, as each array element can allow only one request per L regardless of collisions. The sketch can therefore be sized to keep delivery rate below the maximum capacity of the service.
