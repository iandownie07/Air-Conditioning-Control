//
//  CreateString.cpp
//  Código de empacotar eventos do sistema para que seja inseridos na fila de armazenamento
//
//  Created by Ian Downie on 04/04/21.
//

#include "CreateString.h"   // inclui header da classe




void Packet::setEventTime(int nYr, int nMo, int nDay, int nSeg, int nMin, int nHr)
// método para produzir um único string do tempo de um evento
{
    
    Yr = standardLength(to_string(nYr)); Mo = standardLength(to_string(nMo));  Day = standardLength(to_string(nDay));
    Seg = standardLength(to_string(nSeg)); Min = standardLength(to_string(nMin)); Hr = standardLength(to_string(nHr));
    // "standardLength" acrescenta um '0' caso uma variável só tenha 1 digito
    event_time = Hr+Min+Seg+Day+Mo+Yr;
    // event_time é um string de todos os dados do tempo do evento
}

void Packet::setEvent(int neventtype_flag)
// método para definir o tipo de evento
{
    eventtype_flag = neventtype_flag;
}

void Packet::makePacket()
// método para combinar todos os dados de um evento num único string
{
// ifs para converter "int" em "char"
    if (eventtype_flag == 1)
        event_flag = '1';
    if (eventtype_flag == 2)
        event_flag = '2';
    if (eventtype_flag == 3)
        event_flag = '3';
    
    
  // usa-se "push_back" para acrescentar num novo elemento num string
    event_time.push_back(event_flag);
    // acrescentar um char adicional para sinalizar o fim da transmissão deste evento
    char end = 'e';
    event_time.push_back(end);
    // acrescentar o código deste condicionador de ar
    string code = "1875";
    event_time.insert(0, code);// hot-tub code
    // converter "event_time" em "packet" para ter um nome mais apropriado
    packet = event_time;
}

string Packet::getPacket()
//método para retornar um pacote que possa ser inserido na fila
{
    return packet;
}

string Packet::standardLength(string input_string)
// método para padronizar o formato das varáiveis de tempo
{
    if (input_string.size() == 1)
    {
        string add_zero = "0";
        input_string.insert(0, add_zero);
    }
    return input_string;
}

/*
 int main ()
 {
 Packet pack;
 string output;
 pack.setStoph_Flag(false);
 pack.setStarth_Flag(true);
 pack.setEvent(1);
 pack.setEventTime(16, 5, 21, 50, 54, 16);
 pack.makePacket();
 output = pack.getPacket();
 cout << output << endl;
 }
 
 */
