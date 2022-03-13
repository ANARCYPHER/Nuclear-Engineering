-- Alvaro Fernandez Velazquez (a_fernandez@usal.es)
-- Francisco Blazquez Matias (fran_blm@usal.es)
with Text_IO;

package body Monitor is
   protected body Reactor is
      procedure leer (temp: out Integer) is
      begin
         temp := temperatura;
      end leer;

      procedure incrementar(incremento:Integer) is
      begin
         temperatura := temperatura + incremento;
      end incrementar;

      procedure decrementar(decremento:Integer) is
      begin
         temperatura := temperatura - decremento;
      end decrementar;

      procedure abrirPuerta is
      begin
         nextTime := bajarPeriodo + Clock;
         Ada.Real_Time.Timing_Events.Set_Handler(bajarJitterControl, nextTime, Timer'Access);
      end abrirPuerta;

      procedure cerrarPuerta is
      begin
         Ada.Real_Time.Timing_Events.Set_Handler(bajarJitterControl, nextTime, NULL);
      end cerrarPuerta;

      procedure Timer(event: in out Ada.Real_Time.Timing_Events.Timing_Event) is
      begin
         temperatura := temperatura - 50;
         nextTime := bajarPeriodo + Clock;
         --Eliminar comprobacion
         Text_IO.Put_Line("temperatura bajada: " & temperatura'Img);
         Ada.Real_Time.Timing_Events.Set_Handler(bajarJitterControl, nextTime, Timer'Access);
      end Timer;

   end Reactor;
end Monitor;
