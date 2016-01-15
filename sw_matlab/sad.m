function[time_series, power_spectra, tsc] = sad(time_series, num_channels, decay_rate, symbols, DWL, RWL)
%Generate a spectrum.
t = ones(size(time_series)); for i=1:length(t) t(i) = t(i)*i; end

fprintf('Calculating spectrum.\n');
tic;
power_spectra = abs(ewrndft(time_series, t, num_channels, decay_rate));
toc;

power_spectra = power_spectra(:,1:size(power_spectra,2)/2);

fprintf('Calculating symbolic anomaly score.\n');
tic;
Sts = zeros(size(power_spectra));
for i=1:size(power_spectra,2)
    ts = power_spectra(:,i);
    ts = ts/max(ts);
    Sts(:,i) = floor(ts*(symbols-1)+0.5);
end

Sts2 = zeros(size(power_spectra));
Sts1 = Sts(2:end,:) + 1;
Sts2 = Sts(1:end-1,:) + 1;

%Generate histogram.
sc=zeros(size(Sts1));
for ch=1:size(Sts1,2)
    RG=zeros(symbols);
    DG=zeros(symbols);
    for i=1:size(Sts1,1)
        RG(Sts1(i,ch),Sts2(i,ch)) = RG(Sts1(i,ch),Sts2(i,ch)) + 1; 
        DG(Sts1(i,ch),Sts2(i,ch)) = DG(Sts1(i,ch),Sts2(i,ch)) + 1; 
        if i > DWL, DG(Sts1(i-DWL,ch),Sts2(i-DWL,ch)) = DG(Sts1(i-DWL,ch),Sts2(i-DWL,ch)) - 1; end
        if i > RWL, RG(Sts1(i-RWL,ch),Sts2(i-RWL,ch)) = RG(Sts1(i-RWL,ch),Sts2(i-RWL,ch)) - 1; end
        if i > RWL, sc(i,ch) = sum(sum((DG./DWL - RG./RWL).*(DG./DWL - RG./RWL)));
        elseif i > DWL, sc(i,ch) = sum(sum((DG./DWL - RG./i).*(DG./DWL - RG./i)));
        else sc(i,ch) = sum(sum((DG./i - RG./i).*(DG./i - RG./i))); end
    end
end
tsc = sum(sc, 2);
tsc = tsc/max(tsc);
for i=1:size(sc,2), sc(:,i) = sc(:,i)/max(sc(:,i)); end
toc;

end
