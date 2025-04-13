import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';

export default function App() {
  const [temperature, setTemperature] = useState('');
  const [message, setMessage] = useState('');

  const handleTemperatureSubmit = () => {
    if (!isNaN(temperature)) {
      setMessage(`Você informou uma temperatura inicial de ${temperature}°C.`);
    } else {
      setMessage('Por favor, insira um valor numérico válido.');
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.heading}>Insira a Temperatura Inicial</Text>
      <TextInput
        style={styles.input}
        placeholder="Digite a temperatura (°C)"
        keyboardType="numeric"
        value={temperature}
        onChangeText={setTemperature}
      />
      <Button title="Enviar" onPress={handleTemperatureSubmit} />
      {message ? <Text style={styles.result}>{message}</Text> : null}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#f5f5f5',
    padding: 20,
  },
  heading: {
    fontSize: 20,
    marginBottom: 20,
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    width: '80%',
    marginBottom: 20,
    paddingHorizontal: 10,
    borderRadius: 5,
  },
  result: {
    marginTop: 20,
    fontSize: 16,
    color: 'green',
  },
});
