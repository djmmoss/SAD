clear all;

ttype = 'synth'; %mg, ecg1, ecg2, ecg3, ecg4, ecg5, tek1, tek2, tek3, mitdb, mitdbx, nprs43, nprs44, pow, qtdbsel102, qtdbsele0606, 'aud', 'eur', 'dr1_1', 'A', 'ann'.
mape = 0; mse = 0; sym = 1;
data_dir = 'data';
best = 1;
chan_sel = 1;

%RDFT parameters.
ff=0.9;
chans=16;

%Mape and MSE detection parameters.
WL=200;
offset=0;
sparse=1;
index=floor(WL*0.6);

%reference and detection window lengths.
RWL=3000;
DWL=1000;
symbols = 8;
levels = 2;

if strcmp(ttype, 'mg')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %Import MG time series.
    x = load(sprintf('%s/mg30.dat', data_dir));
    x = x - mean(x); %Make symmetrical.
    x = x/(max(abs(x))); %Normalise.
    
    %Create some anomalies.
    an = zeros(size(x));
    an(3001) = 1;
    an(3101:3120) = 1;
    an(3201:3300) = binornd(1,0.1,100,1);
    
    an = an.*(-1 + 2*rand(size(x)));
    
    for i=1:length(x)
        if an(i) ~= 0
            x(i) = an(i);
        end
    end
end

if strcmp(ttype, 'ecg1')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import eeg time series.
    raw = load(sprintf('%s/chfdbchf15.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'ecg3')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import eeg time series.
    raw = load(sprintf('%s/chfdb_chf13_45590.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'ecg5')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import eeg time series.
    raw = load(sprintf('%s/ltstdb_20321_240.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'tek1')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.9;
        chans=16;
        %reference and detection window lengths.
        RWL=3000;
        DWL=1000;
        symbols = 8;
    end
    %import TEK time series.
    raw = load(sprintf('%s/TEK14.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'tek2')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.9;
        chans=16;
        
        %reference and detection window lengths.
        RWL=3000;
        DWL=1000;
        symbols = 6;
        levels = 2;
    end
    %import TEK time series.
    raw = load(sprintf('%s/TEK16.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'tek3')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.9;
        chans=16;
        
        %reference and detection window lengths.
        RWL=3000;
        DWL=1000;
        symbols = 6;
        levels = 2;
    end
    %import TEK time series.
    raw = load(sprintf('%s/TEK17.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'tek4')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.95;
        chans=64;
        %reference and detection window lengths.
        RWL=5000;
        DWL=1000;
        symbols = 4;
    end
    %import TEK time series.
    raw = load(sprintf('%s/TEK14.txt', data_dir));
    ch1 = raw(:,1);
    raw = load(sprintf('%s/TEK16.txt', data_dir));
    ch1 = [ch1; raw(:,1)];
    raw = load(sprintf('%s/TEK17.txt', data_dir));
    ch1 = [ch1; raw(:,1)];
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'mitdb')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/mitdb__100_180.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'mitdbx')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/mitdbx_mitdbx_108.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'nprs43')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import TEK time series.
    raw = load(sprintf('%s/nprs43.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'nprs44')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import TEK time series.
    raw = load(sprintf('%s/nprs44.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'pow')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import TEK time series.
    raw = load(sprintf('%s/power_data.txt', data_dir));
    ch1 = raw(:,1);
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'synth')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import TEK time series.
    ch1 = load("sig.out");
    t = zeros(size(ch1,1),1);
    for i=1:length(t) t(i) = i; end
    %ch1 = ch1 - mean(ch1);
    %ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'qtdbsel102')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/qtdbsel102.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'qtdbsele0606')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=300;
        DWL=100;
        symbols = 8;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/qtdbsele0606.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'aud')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.999;
        chans=64;
        %reference and detection window lengths.
        RWL=1000;
        DWL=100;
        symbols = 16;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/aud_ml.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'eur')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.995;
        chans=1024;
        %reference and detection window lengths.
        RWL=2000;
        DWL=500;
        symbols = 8;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/eur_ml.txt', data_dir));
    t = raw(:,1);
    ch1 = raw(:,2);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
end

if strcmp(ttype, 'dr1_1')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.1;
        chans=16;
        %reference and detection window lengths.
        RWL=30;
        DWL=10;
        symbols = 8;
        chan_sel = 1;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/dr1_1.txt', data_dir));
    t = raw(:,2);
    ch1 = raw(:,1);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'dr1_2')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.95;
        chans=16;
        %reference and detection window lengths.
        RWL=30;
        DWL=10;
        symbols = 8;
        chan_sel = 1;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/dr1_2.txt', data_dir));
    t = raw(:,2);
    ch1 = raw(:,1);
    ch2 = raw(:,3);
    t = t - t(1);
    t = t/(t(2)-t(1));
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
end

if strcmp(ttype, 'A')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.6;
        chans=32;
        %reference and detection window lengths.
        RWL=2000;
        DWL=100;
        symbols = 16;
        chan_sel = 1;
        syn_an=1;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/A.cont', data_dir));
    ch1 = raw(:,1);
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    x = ch1;
    t = zeros(length(x),1);
    for i=1:length(t) t(i) = i; end

    if syn_an == 1
        err_len = 1000;
        period = 20;
        y = 1:err_len;
        y = y';
        w1 = 0; w2 = 4E-2; w3 = 2E-2; w4 = 2E-2;
        err_sig = w1*(repmat(-1, err_len, 1) + 2*rand(err_len,1)) + w2*sin(y./period + repmat(2*pi*rand(1), err_len,1)) + w3*sin(2*y./period + repmat(2*pi*rand(1), err_len,1)) + w4*sin(3*y./period + repmat(2*pi*rand(1), err_len,1));
        x(5501:6500) = x(5501:6500) + err_sig;
    end
end

if strcmp(ttype, 'ann')
    %Override parameters with the best I've found so far.
    if best == 1
        %RDFT parameters.
        ff=0.99;
        chans=16;
        %reference and detection window lengths.
        RWL=600;
        DWL=100;
        symbols = 8;
        chan_sel = 1;
    end
    %import mitdb time series.
    raw = load(sprintf('%s/ann_gun_CentroidA', data_dir));
    ch1 = raw(:,1);
    ch2 = raw(:,2);
    ch1 = ch1 - mean(ch1);
    ch1 = ch1/(max(abs(ch1)));
    ch2 = ch2 - mean(ch2);
    ch2 = ch2/(max(abs(ch2)));
    if chan_sel == 2
        x = ch2;
    else
        x = ch1;
    end
    t = zeros(length(x),1);
    for i=1:length(t) t(i) = i; end
    s = 501;
    e = 3500;
end

[time_series, power_spectra, total_anomaly_score] = sad(x, chans, ff, symbols, DWL, RWL);
