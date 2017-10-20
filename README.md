# TimedAccumulator

Something I found myself doing over and over. I want to accumulate some values over some time interval. At the end of the time interval I want to for example dispatch the value to some REST API or persist it to a database.

No checking for overflowing values in the accumulator. Untested.

## Example

```cpp
using namespace std::chrono;
TimedAccumulator<unsigned int> bitrate(seconds(1));

while(true)
{
    auto video_frame = decoder.get_frame();

    bitrate.accumulate(video_frame.size,
    [](unsigned int accu)
    {
        std::cout << "Bitrate per second: " << accu << std::endl;
    });
}
```