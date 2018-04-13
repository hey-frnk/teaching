clear;
clc;

% Schoenere Farben
clr_teal = [0 102 204] ./ 255;
clr_mRed = [255 0 127] ./ 255;

% Signale einlesen
% d1: Abtastsignal
% d2: Nachrichtensignal (Sinus)
% d3: Abgetastetes Signal
% d4: Uebertragenes Signal
% d5: Rekonstruiertes Signal
[t, d1, d2, d3, d4, d5] = textread('output.txt', '%f %f %f %f %f %f', 5000);

[t2, i1] = textread('output_chImpulse.txt', '%f %f', 250);
[t3, i2] = textread('output_lpImpulse.txt', '%f %f', 2000);

figure(1);

% Plot Abtastung
subplot(311);
plot(t, d1, 'Color', clr_teal);
hold on;
plot(t, d2, 'red-.', t, d3, 'black');
hold off;
xlim([min(t) max(t)]);
xlabel('t [s]');
ylabel('Amplitude [V]');
title(['Nachrichtensignal nach Abtastung']);
legend('Abtastsignal', 'Nachrichtensignal', 'Abgetastetes Signal', 'Location', 'southeast');
grid on;

% Plot Kanaluebertragung
subplot(312);
plot(t, d3, 'black');
hold on;
plot(t, d4, 'Color', clr_teal);
hold off;
xlim([min(t) max(t)]);
ylim([min(d4) max(d4)]);
xlabel('t [s]');
ylabel('Amplitude [V]');
title(['Nachrichtensignal nach Kanaluebertragung']);
legend('Abgetastetes Signal', 'Empfangenes Signal', 'Location', 'southeast');
grid on;

% Plot Signalrekonstruktion
subplot(313);
plot(t, d2, 'black');
hold on;
plot(t, d5, 'Color', clr_teal);
hold off;
xlim([min(t) max(t)]);
ylim([min([min(d2) min(d5)]) max([max(d2) max(d5)])]);
xlabel('t [s]');
ylabel('Amplitude [V]');
title(['Nachrichtensignal nach Rekonstruktionsfilterung']);
legend('Urspr. Signal', 'Rek. Signal', 'Location', 'northeast');
grid on;

gr = gcf;
gr.Position = [100 100 700 600];


figure(2);

subplot(211);
plot(t2, i1);
xlim([min(t2) max(t2)]);
xlabel('t [s]');
ylabel('Amplitude [V]');
title(['Impulsantwort Kanal']);
grid on;

subplot(212);
plot(t3, i2);
xlim([min(t3) max(t3)]);
xlabel('t [s]');
ylabel('Amplitude [V]');
title(['Impulsantwort Rekonstruktionsfilter']);
grid on;

gr = gcf;
gr.Position = [100 100 700 300];