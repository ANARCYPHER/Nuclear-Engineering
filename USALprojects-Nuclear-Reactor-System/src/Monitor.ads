--Alvaro Fernandez Velazquez (a_fernandez@usal.es)
--Francisco Blazquez Matias (fran_blm@usal.es)
with Ada.Real_Time;
with Ada.Real_Time.Timing_Events;
use Ada.Real_Time;
package Monitor is
   protected type Reactor is
      procedure leer(temp : out Integer);
      procedure incrementar(incremento:Integer);
      procedure decrementar(decremento:Integer);
      procedure abrirPuerta;
      procedure cerrarPuerta;
      procedure Timer(event: in out Ada.Real_Time.Timing_Events.Timing_Event);
   private
      temperatura:Integer := 1450;
      bajarJitterControl:Ada.Real_Time.Timing_Events.Timing_Event;
      bajarPeriodo:Ada.Real_Time.Time_Span:= Ada.Real_Time.Seconds(1);
      nextTime:Ada.Real_Time.Time;
   end Reactor;
end Monitor;


