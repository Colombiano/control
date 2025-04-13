% Example of PID temperature Control System of  writted in Octave Language 
% Exemplo de um sistema de controle PDI de temperatura escrito em linguagem Octave
% Comments in portuguese

% Parâmetros do sistema
Kp = 2.0;  % Ganho Proporcional
Ki = 0.5;  % Ganho Integrativo
Kd = 0.1;  % Ganho Derivativo
setpoint = 50; % Temperatura desejada (°C)
dt = 1;    % Intervalo de tempo (s)
tempo_simulacao = 100; % Duração da simulação (s)

% Variáveis de inicialização
erro_acumulado = 0;
erro_anterior = 0;
temperatura = 20; % Temperatura inicial (°C)
historico_temperatura = []; % Para armazenar os valores para visualização

% Loop de controle
for t = 1:tempo_simulacao
    erro = setpoint - temperatura; % Cálculo do erro
    erro_acumulado += erro * dt; % Parte Integrativa
    derivativo = (erro - erro_anterior) / dt; % Parte Derivativa
    
    % Sinal de controle (saída do controlador)
    controle = Kp * erro + Ki * erro_acumulado + Kd * derivativo;
    
    % Simulação do comportamento do sistema (exemplo simples)
    temperatura += controle * 0.1; % Ajuste da temperatura com base no controle
    erro_anterior = erro;
    
    % Armazenar temperatura para visualização
    historico_temperatura = [historico_temperatura, temperatura];
end

% Plot dos resultados
tempo = 1:tempo_simulacao;
plot(tempo, historico_temperatura, 'b-', 'LineWidth', 2);
hold on;
plot(tempo, setpoint * ones(size(tempo)), 'r--', 'LineWidth', 2);
xlabel('Tempo (s)');
ylabel('Temperatura (°C)');
legend('Temperatura Atual', 'Setpoint');
title('Controle PDI de Temperatura');
grid on;
