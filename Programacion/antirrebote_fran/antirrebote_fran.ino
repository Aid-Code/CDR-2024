#define CUENTAS_RESET 5
#define BTN A4

bool estado_previo[3];
uint8_t contador[3] = {0,0,0};

bool flag_evento[3] = {false,false,false};
bool flag_tipo[3] = {false,false,false};

auto prev_dbnc_millis = millis();

void funcion_debounce(void)
{
  for(uint8_t i = 0; i < 3; i++)
  {
    bool estado_actual = digitalRead(pines_dbnc[i]);

    if(estado_actual != estado_previo[i])
    {
      contador[i] = CUENTAS_RESET;
    }
    else
    {
      if(contador[i] > 0)
      {
        contador[i]--;

        if(contador[i] == 0)
        {
          flag_evento[i] = true;
          flag_tipo[i] = estado_actual;
        }
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  for(uint8_t i = 0; i < 3; i++)
  {
    pinMode(pines_dbnc[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  auto curr_millis = millis();
  if(curr_millis - prev_dbnc_millis >= 1)
  {
    prev_dbnc_millis = curr_millis;

    funcion_debounce();
  }
}
