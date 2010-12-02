#include "TracePoint.hpp"
#include "TaskProjection.hpp"
#include <limits.h>

TracePoint::TracePoint(const AIRCRAFT_STATE &state):
    SearchPoint(state.Location),
    ALTITUDE_STATE(state),
    VARIO_STATE(state),
    time((int)state.Time),
    last_time(UINT_MAX),
    drift_factor(state.thermal_drift_factor())
{

}

TaskProjection get_bounds(const TracePointVector& trace,
                          const GeoPoint &fallback_location) 
{
  TaskProjection task_projection;

  task_projection.reset(fallback_location);
  for (TracePointVector::const_iterator it = trace.begin(); 
       it != trace.end(); ++it) {
    task_projection.scan_location(it->get_location());
  }
  task_projection.update_fast();
  return task_projection;
}
