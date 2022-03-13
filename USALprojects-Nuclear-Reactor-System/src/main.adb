--Alvaro Fernandez Velazquez (a_fernandez@usal.es)
--Francisco Blazquez Matias (fran_blm@usal.es)

with Monitor;
with Text_IO;
use Monitor;
with Ada.Calendar;
with Ada.Numerics;
with Ada.Real_Time;
with Ada.Numerics.Discrete_Random;
use Ada.Calendar;
procedure Main is
   type Reactores is array (1..3) of aliased Reactor;
   subtype aleatorioReactor is Integer range 1..3;
   package Aleatorio is new Ada.Numerics.Discrete_Random(aleatorioReactor);
   --Tarea de aumento de temperatura
   task type Temperatura( r: access Reactores);
   task body Temperatura is
      intervalo:Duration:= 2.0;
      nextTime:Time;
      seed:Aleatorio.Generator;
      temp:aleatorioReactor;
   begin
      Aleatorio.Reset(seed);
      nextTime := Clock + intervalo;
      loop
         -- Subir temperatura aleatoriamente
         temp := Aleatorio.Random(seed);
         r(temp).incrementar(150);
         --Eliminar la comprobacion
         Text_IO.Put_Line("Incrementando temperatura de " & temp'Img);
         delay until nextTime;
         nextTime := Clock + intervalo;
      end loop;
   end Temperatura;
   --Tarea del Sensor
   task type Sensor(r: access Reactor) is
      entry leer( result: out Integer);
   end Sensor;
   task body Sensor is
      intervalo:Duration:= 1.0;
      nextTime:Time;
   begin
      loop
         select
            accept leer(result: out Integer) do
               nextTime := intervalo + Clock;
               r.leer(result);
               delay until nextTime;
            end leer;
         or
              terminate;
         end select;
      end loop;
   end Sensor;
   -- Tarea del Actuador
   task type Actuador(r: access Reactor; id: Integer) is
      entry abrir;
      entry cerrar;
   end Actuador;
   task body Actuador is
      moverPuertaIntervalo:Duration:= 0.1;
      movidaTimer:Time;
      cerrado:Boolean := true;
   begin
      loop
         select
            accept abrir do
               begin
                  if cerrado = true then
                     --Eliminar comprobacion
                     Text_IO.Put_Line("abriendo compuerta reactor: " & id'Img);
               	     movidaTimer := Clock + moverPuertaIntervalo;
                     delay until movidaTimer;
                     r.abrirPuerta;
                     Text_IO.Put_Line("abierto compuerta reactor: " & id'Img);
                     cerrado := false;
                  end if;
               end;
            end abrir;
         or
            accept cerrar do
               begin
                  if cerrado = false then
                     Text_IO.Put_Line("cerrando compuerta reactor: " & id'Img);
                     movidaTimer := Clock + moverPuertaIntervalo;
                     delay until movidaTimer;
                     r.cerrarPuerta;
                     Text_IO.Put_Line("cerrado compuerta reactor: " & id'Img);
                     cerrado := true;
                  end if;

               end;
            end cerrar;
         or
              terminate;
         end select;
      end loop;
   end Actuador;

   -- Tarea del Controlador
   task type Controlador is
      entry avisarme;
   end Controlador;
   task body Controlador is
   begin
      loop
         select
            accept avisarme  do
               begin
                  null;
               end;
            end avisarme;
         or delay 3.0;
            Text_IO.Put_Line("¡¡¡¡Alarma!!!!");
         end select;
      end loop;
   end Controlador;

   --Tarea de la tarea del reactor
   task type reactorTask (r: access Reactor; id: Integer) is
      private
   end reactorTask;
   task body reactorTask is
      sen:Sensor(r);
      act:Actuador(r, id);
      con:Controlador;
      intervalo:Duration:= 2.0;
      nextTimer:Time;
      inicioIntervalo:Duration:= 0.5;
      inicio:Time;
      temperatura:Integer;
   begin
      inicio := inicioIntervalo + Clock;
      delay until inicio;
      nextTimer := intervalo + Clock;
      loop
         sen.leer(temperatura);
         --Eliminar comprobacion
         Text_IO.Put_Line("Temperatura: " & temperatura'Img & " Reactor: " & id'Img);
         if temperatura >= 1500 then
            act.abrir;
            if temperatura > 1750 then
               Text_IO.Put_Line("¡¡¡Alarma temperatura!!! " & temperatura'Img & " Reactor: " & id'Img);
            end if;
         elsif temperatura < 1500 then
            act.cerrar;
         end if;
         con.avisarme;
         delay until nextTimer;
         nextTimer := intervalo + Clock;
      end loop;
   end;
   --Procedimiento de lanzar las tareas
   procedure inicio is
      rs : aliased Reactores;
      t: Temperatura(rs'Access);
      r1: reactorTask(rs(1)'Access, 1);
      r2: reactorTask(rs(2)'Access, 2);
      r3: reactorTask(rs(3)'Access, 3);
   begin
      null;
   end;
begin
   inicio;
end Main;
