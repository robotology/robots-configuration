% First of all you have to double click on the .mat file to load the
% ergocub_head variable

close all

% set defaults so plots look nice
set(groot,'defaultLineLineWidth',1.3);
set(groot,'defaultAxesFontSize',12);
set(groot,'defaultAxesMinorGridAlpha', 1);
set(groot,'defaultAxesXMinorGrid','on','defaultAxesXMinorGridMode','manual');
set(groot,'defaultAxesYMinorGrid','on','defaultAxesYMinorGridMode','manual');

joints_pos = timeseries(squeeze(ergocub_head.joints_state.positions.data(1:2, 1, :))', ...
    ergocub_head.joints_state.positions.timestamps - ergocub_head.joints_state.positions.timestamps(1), ...
    "Name", ergocub_head.joints_state.positions.name);
joints_refs = timeseries(squeeze(ergocub_head.PIDs.position_reference.data(1:2, 1, :))', ...
    ergocub_head.PIDs.position_reference.timestamps - ergocub_head.PIDs.position_reference.timestamps(1), ...
    "Name", ergocub_head.PIDs.position_reference.name);

pwms = timeseries(squeeze(ergocub_head.motors_state.PWM.data(1:2, 1, :))', ...
    ergocub_head.motors_state.PWM.timestamps - ergocub_head.motors_state.PWM.timestamps(1), ...
    "Name", ergocub_head.motors_state.PWM.name);

currents = timeseries(squeeze(ergocub_head.motors_state.currents.data(1:2, 1, :))', ...
    ergocub_head.motors_state.currents.timestamps - ergocub_head.motors_state.currents.timestamps(1), ...
    "Name", ergocub_head.motors_state.currents.name);

figure
tiledlayout(3,2,"TileSpacing","tight")
h(1) = nexttile;
plot(joints_pos.Time, joints_pos.Data(:,1))
hold on
plot(joints_refs.Time, joints_refs.Data(:,1), "k--")
legend({"pitch", "pitch ref"})
ylabel("pitch (deg)")

h(2) = nexttile;
plot(joints_pos.Time, joints_pos.Data(:,2))
hold on
plot(joints_refs.Time, joints_refs.Data(:,2), "k--")
legend({"roll", "roll ref"})
ylabel("roll (deg)")

h(3) = nexttile;
plot(pwms.Time, pwms.Data(:,1))
ylabel("pwm 0 (perc)")

h(4) = nexttile;
plot(pwms.Time, pwms.Data(:,2))
ylabel("pwm 1 (perc)")

h(3) = nexttile;
plot(currents.Time, currents.Data(:,1))
ylabel("current 0 (A)")
xlabel("Times (sec)")

h(4) = nexttile;
plot(currents.Time, currents.Data(:,2))
ylabel("current 1 (A)")
xlabel("Times (sec)")

linkaxes(h, "x")